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

  public ObjectId addUser(String username) {
    collection = database.getCollection("users");
    Bson usernameFilter = Filters.eq("username", username);
    Document response = collection.find(usernameFilter).first();
    if (response != null) {
      System.out.println("please enter a unique username");
      return null;
    } else {
      Document user = new Document("username", username)
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
      .append("player1symbol", symbol1)
      .append("player2", player2)
      .append("player2symbol", symbol2)
      .append("completed", false)
      .append("winner", null)
      .append("count", 1);
    collection.insertOne(game);
    System.out.println("Game created");

    return (ObjectId) game.get("_id");
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
    System.out.println("move logged");

    return (ObjectId) move.get("_id");
  }
}

final char _MOVE = 'm';
final float ONE_ONE = 1.1;
final float ONE_TWO = 1.2;
final float ONE_THREE = 1.3;
final float TWO_ONE = 2.1;
final float TWO_TWO = 2.2;
final float TWO_THREE = 2.3;
final float THREE_ONE = 3.1;
final float THREE_TWO = 3.2;
final float THREE_THREE = 3.3;

//Serial port for communication to/from Arduino
private Serial com4, com5;
private String message;
private boolean com4Connected, com5Connected;
private boolean switched = false;
private int moveNo = 0;

//object id values for mongo database
private ObjectId gameId;
private Player player1, player2;

public void setup() {
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here

  com4 = new Serial(this, "COM8", 9600);
  //com5 = new Serial(this, "COM5", 9601);
  com4.bufferUntil('\n');
  //com5.bufferUntil('\n');

  //get user data
  initialisePlayers();
}

public void draw() {
  background(230);
}

public void initialisePlayers() { 
  Mongo mongo = new Mongo();
  ObjectId id;
  String username;
  char symbol;

  username = JOptionPane.showInputDialog("Player 1 Name: ");
  do {
    symbol = JOptionPane.showInputDialog("Player 1 Symbol (Please enter 'X' or 'O'): ").charAt(0);
  } while (!(symbol == 'X' || symbol == 'x' || symbol == 'O' || symbol == 'o'));
  id = mongo.addUser(username);
  player1 = new Player(id, username, symbol, true);

  if (player1.getPlayerSymbol() == 'X') {
    symbol = 'O';
  } else {
    symbol = 'X';
  }
  username = JOptionPane.showInputDialog("Player 2 Name (symbol '" + symbol + "'): ");
  id = mongo.addUser(username);
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

    if (myPort == com4) {
      if (!com4Connected) { //executes on first message received
        if (message.equals("requestcontact")) {
          myPort.clear();
          com4Connected = true;
          myPort.write('t');
          txtOutput.setText("Connection to Arduino established! (COM4)");
        }
      } else { //on all subsequent messages after contact established
        txtOutput.setText(message);
        if (message.equals("movecomplete")) {
          float updatedPos = 0;
          while (myPort.available() < 0) {
            delay(500);
            System.out.println("awaiting coordinate");
          }
          updatedPos = Float.parseFloat(myPort.readString());

          //database connection instance
          Mongo mongo = new Mongo();   
          if (isFirstMove()) {
            //create game record once first move is complete
            gameId = mongo.createGame(player1.getMongoId(), player1.getPlayerSymbol(), player2.getMongoId(), player2.getPlayerSymbol());
          }

          //record the moves on database
          //need to get updated position back from Arduino
          Player player = getCurrentPlayer();
          mongo.addMove(gameId, player.getMongoId(), player.getLastKnownPos(), updatedPos);
          player.setLastKnownPos(updatedPos);

          toggleSlider();
        }
      }
    } /*else if (myPort == com5) {
     if (!com5Connected) { //executes on first message received
     if (message.equals("requestcontact")) {
     myPort.clear();
     com5Connected = true;
     myPort.write('t');
     txtOutput.setText("Connection to Arduino established! (COM5)");
     }
     } else { //on all subsequent messages after contact established
     txtOutput.setText(message);
     toggleSlider();
     }*/
    //}
  }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI() {
}

/*public Serial getCurrentPort() {
 if (sldrTurn.getValueI() == 0) {
 if (!switched) {
 return com4;
 } else {
 return com5;
 }
 } else if (sldrTurn.getValueI() == 100) {
 if (!switched) {
 return com5;
 } else {
 return com4;
 }
 }*/

public Serial getCurrentPort() {
  return com4;
}

public void toggleSlider() {
  if (moveNo == 0) {
    System.out.println("player 1 symbol is '" + player1.getPlayerSymbol() + "'");
    if (player1.getPlayerSymbol() == 'O') {
      System.out.println("'" + player1.getPlayerSymbol() + "' == 'O'");
      sldrTurn.setValue(0.0);
      System.out.println(sldrTurn.getValueF());
    } else if (player1.getPlayerSymbol() == 'X') {
      System.out.println("'" + player1.getPlayerSymbol() + "' == 'X'");
      sldrTurn.setValue(1.0);
      System.out.println("the ting is " + sldrTurn.getValueF());
      System.out.println(sldrTurn.getValueF());
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
  return moveNo == 1;
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