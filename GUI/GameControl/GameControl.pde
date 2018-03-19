// Need G4P library
import g4p_controls.*;
import processing.serial.*;
import javax.swing.JOptionPane;

public class Mongo {

  private String db;
  private String coll;
  private MongoCollection<Document> collection;
  private MongoDatabase database;
  private MongoClient mongoClient;
  //private User user = new User();

  public Mongo() {
    mongoClient = new MongoClient("localhost", 27017);
    database = mongoClient.getDatabase("naughts_and_crosses");
  }

  public ObjectId addUser(String username) {
    collection = database.getCollection("users");
    Document user = new Document("username", username)
      .append("count", 1);
    collection.insertOne(user);
    System.out.println("Account registered");

    return (ObjectId) user.get("_id");
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
      .append("moveOrder", moveNo++)
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

boolean isNaught = false;

//Serial port for communication to/from Arduino
private Serial com4, com5;
private String message;
private boolean com4Connected, com5Connected;
private boolean isFirstMove = true;
private boolean switched = false;
private int moveNo = 0;

private String player1Name, player2Name;
private char player1Symbol, player2Symbol;
private ObjectId player1Id, player2Id, gameId;
private float player1LastKnownPos, player2LastKnownPos;

public void setup() {
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here

  com4 = new Serial(this, "COM6", 9600);
  //com5 = new Serial(this, "COM5", 9601);
  com4.bufferUntil('\n');
  //com5.bufferUntil('\n');

  Mongo mongo = new Mongo();
  player1Name = JOptionPane.showInputDialog("Player 1 Name: ");
  player1Id = mongo.addUser(player1Name);
  player2Name = JOptionPane.showInputDialog("Player 2 Name: ");
  player2Id = mongo.addUser(player2Name);
}

public void draw() {
  background(230);
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

          Mongo mongo = new Mongo();
          if (isFirstMove) {
            if (isNaught) {
              player1Symbol = 'O';
              player2Symbol = 'X';
            } else {
              player1Symbol = 'X';
              player2Symbol = 'O';
            }
            gameId = mongo.createGame(player1Id, player1Symbol, player2Id, player2Symbol);
          }

          //record the moves on database
          //need to get updated position back from Arduino
          if (isNaught) {
            if (player1Symbol == 'O') {
              mongo.addMove(gameId, player1Id, player1LastKnownPos, updatedPos);
              player1LastKnownPos = updatedPos;
            } else {
              mongo.addMove(gameId, player2Id, player2LastKnownPos, updatedPos);
              player2LastKnownPos = updatedPos;
            }
          } else {
            if (player1Symbol == 'X') {
              mongo.addMove(gameId, player1Id, player1LastKnownPos, updatedPos);
              player1LastKnownPos = updatedPos;
            } else {
              mongo.addMove(gameId, player2Id, player2LastKnownPos, updatedPos);
              player1LastKnownPos = updatedPos;
            }
          }

          toggleSlider();
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
  if (sldrTurn.getValueI() == 0) {
    isNaught = false;
    sldrTurn.setValue(100);
  } else if (sldrTurn.getValueI() == 100) {
    isNaught = true;
    sldrTurn.setValue(0);
  }

  if (isFirstMove) {
    isFirstMove = false;
    sldrTurn.setEnabled(false);
  }
}

public char getSliderSymbol() {
  if (sldrTurn.getValueI() == 0) {
    return 'O';
  } else if (sldrTurn.getValueI() == 100) {
    return 'X';
  }

  return ' ';
}