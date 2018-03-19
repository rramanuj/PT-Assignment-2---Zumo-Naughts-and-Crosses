// Need G4P library
import g4p_controls.*;
import processing.serial.*;

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

public void setup() {
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here

  com4 = new Serial(this, "/dev/cu.usbserial-DA01HMYL", 9600);
  //com5 = new Serial(this, "COM5", 9601);
  com4.bufferUntil('\n');
  //com5.bufferUntil('\n');
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
  return com4; }
  //default


public void toggleSlider() {
  if (sldrTurn.getValueI() == 0) {
    sldrTurn.setValue(100);
  } else if (sldrTurn.getValueI() == 100) {
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