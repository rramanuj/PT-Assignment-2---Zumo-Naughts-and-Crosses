// Need G4P library
import g4p_controls.*;
import processing.serial.*;
import javax.swing.JOptionPane;
import org.bson.types.*;

public class Mongo {
  private String db;
  private String coll;
  private MongoCollection<Document> collection;
  private MongoDatabase database;
  private MongoClient mongoClient;

  public Mongo() {
    mongoClient = new MongoClient("localhost", 27017);
    database = mongoClient.getDatabase("naughts_and_crosses");
  }

  public ObjectId addUser(String username, String password) { 
    collection = database.getCollection("users");
    Bson usernameFilter = Filters.eq("username", username);
    Document response = collection.find(usernameFilter).first();
    if (response != null) {
      System.out.println("please enter a unique username");
      return null;
    } else {
      Document user = new Document("username", username)
        .append("password", password)
        .append("count", 1);
      collection.insertOne(user);
      System.out.println("Account registered");

      return (ObjectId) user.get("_id");
    }
  }

  public ObjectId createGame(ObjectId player1, char symbol1, ObjectId player2, char symbol2) {
    collection = database.getCollection("games");
    Document game = new Document()
      .append("player1", player1)
      .append("player2", player2)
      .append("player2symbol", symbol2)
      .append("completed", false)
      .append("winner", null)
      .append("numMoves", 0)
      .append("count", 1);
    collection.insertOne(game);
    System.out.println("Game created");

    return (ObjectId) game.get("_id");
  }

  public void updateGameWinner(ObjectId gameId, ObjectId winnerId) {
    collection = database.getCollection("games");
    Bson gameFilter = Filters.eq("_id", gameId);

    collection.updateOne(gameFilter, 
      new Document("$set", new Document()
      .append("completed", true)
      .append("winner", winnerId)
      .append("numMoves", moveNo)
      ));
  }

  public ObjectId addMove(ObjectId gameId, ObjectId playerId, float startPos, float endPos) {
    collection = database.getCollection("moves");
    Document move = new Document()
      .append("game", gameId)
      .append("player", playerId)
      .append("startPos", startPos)
      .append("endPos", endPos)
      .append("moveNo", moveNo)
      .append("count", 1);
    collection.insertOne(move);
    System.out.println("Move logged.");

    return (ObjectId) move.get("_id");
  }
}

final char _MOVE = 'm';
final char _COMPLETE = 'c';
final char X_SYMBOL = 'X';
final char O_SYMBOL = 'O';

final float ONE_ONE = 1.1;
final float ONE_TWO = 1.2;
final float ONE_THREE = 1.3;
final float TWO_ONE = 2.1;
final float TWO_TWO = 2.2;
final float TWO_THREE = 2.3;
final float THREE_ONE = 3.1;
final float THREE_TWO = 3.2;
final float THREE_THREE = 3.3;

final int FIRST_MOVE = 1;
final int MIN_MOVES = 5;
final int MAX_MOVES = 9;

//Serial port for communication to/from Arduino
private String message;
private Serial port;
private boolean player1Connected, player2Connected;
private boolean switched = false;
private int moveNo = 0;

//object id values for mongo database
private ObjectId gameId;
private Player player1, player2;

public void setup() {

  printArray(Serial.list());
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here

  //get user data from keyboard input
  initialisePlayers();
  port = new Serial(this, "/dev/cu.usbserial-AL1L30FO", 9600);
  port.bufferUntil('\n');
  
  player1.setPort(port);
  player2.setPort(port);
}

public void draw() {
  background(230);
}

public void initialisePlayers() { 
  Mongo mongo = new Mongo();
  ObjectId id;
  String username;
  String password;
  char symbol;

  username = JOptionPane.showInputDialog("Player 1 Name: ");
  password = JOptionPane.showInputDialog("Player 1 Password: ");

  do {
    symbol = JOptionPane.showInputDialog(username + "'s Symbol (Please enter 'X' or 'O'): ").charAt(0);
  } while (!(symbol == X_SYMBOL || symbol == 'x' || symbol == O_SYMBOL || symbol == 'o'));
  id = mongo.addUser(username, password);
  player1 = new Player(id, username, symbol, true);

  if (player1.getPlayerSymbol() == X_SYMBOL) {
    symbol = O_SYMBOL;
  } else {
    symbol = X_SYMBOL;
  }
  username = JOptionPane.showInputDialog("Player 2 Name (symbol '" + symbol + "'): ");
  password = JOptionPane.showInputDialog("Player 2 Password: ");

  id = mongo.addUser(username, password);
  player2 = new Player(id, username, symbol, false);
  toggleSlider();
}

void serialEvent(Serial myPort) {
  //read in data to string
  //new line command indicates end of message
  message = myPort.readString();
  //some value provided from Arduino
  if (message != null) {
    //remove whitespace and formatting
    message = trim(message);
    println(message); //TEST

    if (myPort == player1.getPort()) {
      if (!player1Connected) { //executes on first message received
        if (message.equals("requestcontact")) {
          myPort.clear();
          player1Connected = true;
          myPort.write('t');
          txtOutput.setText("Connection to Arduino established! (player1Arduino)");
        }
      } else { //on all subsequent messages after contact established
        txtOutput.setText(message);
        if (message.equals(_COMPLETE)) {

          char updatedDir;
          while (myPort.available() <= 0) {
            delay(500);
            System.out.println("awaiting direction");
          }
          updatedDir = (char)myPort.read();

          float updatedPos = 0;
          while (myPort.available() <= 0) {
            delay(500);
            System.out.println("awaiting position");
          }
          updatedPos = Float.parseFloat(myPort.readString());

          //database connection instance
          Mongo mongo = new Mongo();   
          if (isFirstMove()) {
            //create game record once first move is complete
            gameId = mongo.createGame(
              player1.getMongoId(), 
              player1.getPlayerSymbol(), 
              player2.getMongoId(), 
              player2.getPlayerSymbol()
              );
          }

          //record the moves on database
          //need to get updated position back from Arduino
          Player player = getCurrentPlayer();
          mongo.addMove(gameId, player.getMongoId(), player.getLastKnownPos(), updatedPos);
          player.setDirection(updatedDir);
          player.setLastKnownPos(updatedPos);

          if (checkWinner(player.getPlayerSymbol())) {
            txtOutput.setText(player.getUsername() + " is the winner!");
            mongo.updateGameWinner(gameId, player.getMongoId());
          } else {
            if (moveLimitReached()) {
              txtOutput.setText("The game is a draw! You're both losers");
              mongo.updateGameWinner(gameId, null);
            }
          }
          toggleSlider();
        }
      }
    } else if (myPort == player2.getPort()) {
      if (!player2Connected) { //executes on first message received
        if (message.equals("requestcontact")) {
          myPort.clear();
          player2Connected = true;
          myPort.write('t');
          txtOutput.setText("Connection to Arduino established! (COM5)");
        }
      } else { //on all subsequent messages after contact established
        txtOutput.setText(message);
        //toggleSlider();
      }
    }
  }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI() {
}

public Serial getCurrentPort() {
  return port;
}

public void toggleSlider() {
  if (moveNo == 0) {
    if (player1.getPlayerSymbol() == O_SYMBOL) {
      sldrTurn.setValue(0.0);
    } else if (player1.getPlayerSymbol() == X_SYMBOL) {
      sldrTurn.setValue(1.0);
    }
    sldrTurn.setEnabled(false);
  } else if (moveNo >= 1) {
    if (sldrTurn.getValueF() == 0.0) {
      sldrTurn.setValue(1.0);
    } else if (sldrTurn.getValueF() == 1.0) {
      sldrTurn.setValue(0.0);
    }
  }
}

public Player getCurrentPlayer() {
  if (player1.isMove(moveNo)) {
    return player1;
  } else {
    return player2;
  }
}

public boolean isFirstMove() {
  return moveNo == FIRST_MOVE;
}

public boolean moveLimitReached() {
  return moveNo == MAX_MOVES;
}

public void updateButtonDisplay(GButton button) {
  Player player = getCurrentPlayer();
  char symbol = player.getPlayerSymbol();
  button.setText(Character.toString(symbol));
  if (symbol == 'X') {
    button.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  } else {
    button.setLocalColorScheme(GCScheme.RED_SCHEME);
  }
}

public boolean checkWinner(char symbol) {
  if (moveNo >= MIN_MOVES) {
    String btnText[][] = {
      {btn1_1.getText(), btn1_2.getText(), btn1_3.getText()}, 
      {btn2_1.getText(), btn2_2.getText(), btn2_3.getText()}, 
      {btn3_1.getText(), btn3_2.getText(), btn3_3.getText()}
    };

    char btnChars[][] = new char[3][3];
    for (int i = 0; i < btnText.length; i++) {
      for (int j = 0; j < btnText[i].length; j++) {
        if (!btnText[i][j].equals("")) {
          if (btnText[i][j].charAt(0) == X_SYMBOL || btnText[i][j].charAt(0) == O_SYMBOL) {
            btnChars[i][j] = btnText[i][j].charAt(0);
          }
        }
      }
    }

    //diagonals can be checked from hard-coded coordinates, only two possible combinations
    return (horzWin(btnChars, symbol) || vertWin(btnChars, symbol) || diagWin(btnChars, symbol));
  }
  //cannot be a winner after fewer than 5 moves
  return false;
}

private boolean diagWin(char[][] chars, char symbol) {
  return ((chars[0][0] == symbol && chars[1][1] == symbol && chars[2][2] == symbol)
    || (chars[2][0] == symbol && chars[1][1] == symbol && chars[0][2] == symbol));
}

private boolean horzWin(char[][] chars, char symbol) {
  return ((chars[0][0] == symbol && chars[0][1] == symbol && chars[0][2] == symbol)
    || (chars[1][0] == symbol && chars[1][1] == symbol && chars[1][2] == symbol)
    || (chars[2][0] == symbol && chars[2][1] == symbol && chars[2][2] == symbol));
}

private boolean vertWin(char[][] chars, char symbol) {
  return ((chars[0][0] == symbol && chars[1][0] == symbol && chars[2][0] == symbol)
    || (chars[0][1] == symbol && chars[1][1] == symbol && chars[2][1] == symbol)
    || (chars[0][2] == symbol && chars[1][2] == symbol && chars[2][2] == symbol));
}