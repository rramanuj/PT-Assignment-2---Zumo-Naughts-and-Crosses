import processing.serial.*;

public class Zumo {
  
  public char symbol;
  public double lastKnownPos;
  public Serial connection;
  public char currDirection;
  
  public Zumo(char sym) {
    symbol = sym;
    lastKnownPos = 3.1f;
    connection = null;
    currDirection = 'N';
  }
}