/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void btn1_1_click1(GButton source, GEvent event) { //_CODE_:btn1_1:211182:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    char indicator;
    if (getCurrentPlayer == player1) {
      indicator = 'x';
    } else {
      indicator = 'y';
    }
    currentPort.write(indicator);
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(ONE_ONE));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(ONE_ONE));

    updateButtonDisplay(source);
  }
} //_CODE_:btn1_1:211182:

public void btn2_2_click1(GButton source, GEvent event) { //_CODE_:btn2_2:245107:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(TWO_TWO));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(TWO_TWO));

    updateButtonDisplay(source);
  }
} //_CODE_:btn2_2:245107:

public void btn2_1_click1(GButton source, GEvent event) { //_CODE_:btn2_1:905140:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(TWO_ONE));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(TWO_ONE));

    updateButtonDisplay(source);
  }
} //_CODE_:btn2_1:905140:

public void btn1_3_click1(GButton source, GEvent event) { //_CODE_:btn1_3:798172:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(ONE_THREE));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(ONE_THREE));

    updateButtonDisplay(source);
  }
} //_CODE_:btn1_3:798172:

public void btn1_2_click1(GButton source, GEvent event) { //_CODE_:btn1_2:745950:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(ONE_TWO));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(ONE_TWO));

    updateButtonDisplay(source);
  }
} //_CODE_:btn1_2:745950:

public void btn2_3_click1(GButton source, GEvent event) { //_CODE_:btn2_3:704356:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(TWO_THREE));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(TWO_THREE));

    updateButtonDisplay(source);
  }
} //_CODE_:btn2_3:704356:

public void btn3_3_click1(GButton source, GEvent event) { //_CODE_:btn3_3:284460:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(THREE_THREE));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(THREE_THREE));

    updateButtonDisplay(source);
  }
} //_CODE_:btn3_3:284460:

public void btn3_2_click1(GButton source, GEvent event) { //_CODE_:btn3_2:320922:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(THREE_TWO));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(THREE_TWO));
    updateButtonDisplay(source);
  }
} //_CODE_:btn3_2:320922:

public void btn3_1_click1(GButton source, GEvent event) { //_CODE_:btn3_1:231294:
  if (!gameEnded) {
    moveNo++;

    Serial currentPort = getCurrentPort();
    
    currentPort.write(_MOVE);
    currentPort.write(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(THREE_ONE));
    System.out.println(str(getCurrentPlayer().getDirection()) + "," + str(getCurrentPlayer().getLastKnownPos()) + "," + str(THREE_ONE));

    updateButtonDisplay(source);
  }
} //_CODE_:btn3_1:231294:

public void txtOutput_change1(GTextArea source, GEvent event) { //_CODE_:txtOutput:438090:
} //_CODE_:txtOutput:438090:

public void sldrTurn_change1(GSlider source, GEvent event) { //_CODE_:sldrTurn:219633:
  float sliderPos = source.getValueF();

  if (sliderPos < 0.50) {
    sliderPos = 0.0;
  } else {
    sliderPos = 1.0;
  }
  sldrTurn.setValue(sliderPos);
} //_CODE_:sldrTurn:219633:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  surface.setTitle("Sketch Window");
  btn1_1 = new GButton(this, 20, 10, 50, 50);
  btn1_1.setLocalColorScheme(GCScheme.SCHEME_8);
  btn1_1.addEventHandler(this, "btn1_1_click1");
  btn2_2 = new GButton(this, 80, 70, 50, 50);
  btn2_2.setLocalColorScheme(GCScheme.SCHEME_8);
  btn2_2.addEventHandler(this, "btn2_2_click1");
  btn2_1 = new GButton(this, 20, 70, 50, 50);
  btn2_1.setLocalColorScheme(GCScheme.SCHEME_8);
  btn2_1.addEventHandler(this, "btn2_1_click1");
  btn1_3 = new GButton(this, 140, 10, 50, 50);
  btn1_3.setLocalColorScheme(GCScheme.SCHEME_8);
  btn1_3.addEventHandler(this, "btn1_3_click1");
  btn1_2 = new GButton(this, 80, 10, 50, 50);
  btn1_2.setLocalColorScheme(GCScheme.SCHEME_8);
  btn1_2.addEventHandler(this, "btn1_2_click1");
  btn2_3 = new GButton(this, 140, 70, 50, 50);
  btn2_3.setLocalColorScheme(GCScheme.SCHEME_8);
  btn2_3.addEventHandler(this, "btn2_3_click1");
  btn3_3 = new GButton(this, 140, 130, 50, 50);
  btn3_3.setLocalColorScheme(GCScheme.SCHEME_8);
  btn3_3.addEventHandler(this, "btn3_3_click1");
  btn3_2 = new GButton(this, 80, 130, 50, 50);
  btn3_2.setLocalColorScheme(GCScheme.SCHEME_8);
  btn3_2.addEventHandler(this, "btn3_2_click1");
  btn3_1 = new GButton(this, 20, 130, 50, 50);
  btn3_1.setLocalColorScheme(GCScheme.SCHEME_8);
  btn3_1.addEventHandler(this, "btn3_1_click1");
  txtOutput = new GTextArea(this, 10, 230, 160, 80, G4P.SCROLLBARS_NONE);
  txtOutput.setOpaque(true);
  txtOutput.addEventHandler(this, "txtOutput_change1");
  sldrTurn = new GSlider(this, 250, 270, 100, 40, 10.0);
  sldrTurn.setLimits(0.5, 0.0, 1.0);
  sldrTurn.setNumberFormat(G4P.DECIMAL, 2);
  sldrTurn.setOpaque(false);
  sldrTurn.addEventHandler(this, "sldrTurn_change1");
  lblX = new GLabel(this, 351, 280, 80, 20);
  lblX.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  lblX.setText("X");
  lblX.setOpaque(false);
  lblO = new GLabel(this, 170, 280, 80, 20);
  lblO.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  lblO.setText("O");
  lblO.setOpaque(false);
}

// Variable declarations 
// autogenerated do not edit
GButton btn1_1; 
GButton btn2_2; 
GButton btn2_1; 
GButton btn1_3; 
GButton btn1_2; 
GButton btn2_3; 
GButton btn3_3; 
GButton btn3_2; 
GButton btn3_1; 
GTextArea txtOutput; 
GSlider sldrTurn; 
GLabel lblX; 
GLabel lblO; 