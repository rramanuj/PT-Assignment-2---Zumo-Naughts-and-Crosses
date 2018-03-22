import processing.serial.*;
import org.bson.types.*;

public class Player {

  ObjectId _id;
  private String username;
  private boolean goesFirst;
  private Zumo zumo;

  public Player(ObjectId id, String name, char sym, boolean first) {
    _id = id;
    username = name;
    goesFirst = first;
    zumo = new Zumo(Character.toString(sym).toUpperCase().charAt(0));
  }

  public ObjectId getMongoId() {
    return _id;
  }

  public String getUsername() {
    return username;
  }

  public void setUsername(String name) {
    username = name;
  }

  public char getPlayerSymbol() {
    return zumo.symbol;
  }

  public void setPlayerSymbol(char sym) {
    zumo.symbol = sym;
  }

  public float getLastKnownPos() {
    return zumo.lastKnownPos;
  }

  public void setLastKnownPos(float pos) {
    zumo.lastKnownPos = pos;
  }

  public boolean isMove(int moveNo) {
    if (goesFirst) {
      return !((moveNo % 2) == 0);
    } else {
      return (moveNo % 2) == 0;
    }
  }
  
  public Serial getPort() {
    return zumo.connection;
  }
  
  public void setPort(Serial port) {
    zumo.connection = port;
  }
  
  public char getDirection() {
    return zumo.currDirection;
  }
  
  public void setDirection(char dir) {
    zumo.currDirection = dir;
  }
}