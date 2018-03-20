import g4p_controls.*;
import org.bson.types.*;

public class Player {

  ObjectId _id;
  private String username;
  private char symbol;
  private boolean goesFirst;
  private float lastKnownPos;

  public Player(ObjectId id, String name, char sym, boolean first) {
    _id = id;
    username = name;
    symbol = Character.toString(sym).toUpperCase().charAt(0);
    goesFirst = first;
    lastKnownPos = 0;
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
    return symbol;
  }

  public void setPlayerSymbol(char sym) {
    symbol = sym;
  }

  public float getLastKnownPos() {
    return lastKnownPos;
  }

  public void setLastKnownPos(float pos) {
    lastKnownPos = pos;
  }

  public boolean isMove(int moveNo) {
    if (goesFirst) {
      return !((moveNo % 2) == 0);
    } else {
      return (moveNo % 2) == 0;
    }
  }
}