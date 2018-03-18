#include <ZumoReflectanceSensorArray.h>


#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
//LSM303 compass;
#define NUM_SENSORS 6

//NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

#include <Servo.h>
/*
 * This example uses the ZumoMotors library to drive each motor on the Zumo
 * forward, then backward. The yellow user LED is on when a motor should be
 * running forward and off when a motor should be running backward. If a
 * motor on your Zumo has been flipped, you can correct its direction by
 * uncommenting the call to flipLeftMotor() or flipRightMotor() in the setup()
 * function.
 */

#define LED_PIN 13
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define BLACK_THRESHOLD 300 // microseconds
#define QTR_THRESHOLD 200  // microseconds

// Speed/duration settings
#define REVERSE_SPEED     200
#define TURN_SPEED        200
#define FORWARD_SPEED     150
#define REVERSE_DURATION  200
#define TURN_DURATION     300

Pushbutton button(ZUMO_BUTTON);
//Created a new version of the code which I've tested with the Arduino that works.
ZumoMotors motors;
ZumoReflectanceSensorArray reflectanceSensors(QTR_NO_EMITTER_PIN);
unsigned int sensor_values[NUM_SENSORS];

void setup()
{
  reflectanceSensors.init();
  reflectanceSensors.calibrate();
  
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("waiting...");
  button.waitForButton();
  //sensor_callibration();
  moveForward();
}

void loop()
{
  reflectanceSensors.read(sensor_values);
  Serial.println(String(sensor_values[0]));
  
  /*if (Serial.available()>0) {
        char motor = (char) Serial.read();
        int pin;
        Servo movingServo;
        String name ="";
        switch (motor)
        {
           case 'w': case 'W': moveForward(); delay(2); break;
           case 'a': case 'A': digitalWrite(LED_PIN, HIGH); motors.setLeftSpeed(0); motors.setRightSpeed(10000); delay(2); break;
           case 's': case 'S': digitalWrite(LED_PIN, HIGH); motors.setLeftSpeed(-10000); motors.setRightSpeed(-10000); delay(2); break;
           case 'd': case 'D': digitalWrite(LED_PIN, HIGH); motors.setLeftSpeed(10000); motors.setRightSpeed(0); delay(2); break;
           case 'q': case 'Q': digitalWrite(LED_PIN, HIGH); motors.setLeftSpeed(0); motors.setRightSpeed(0); delay(2); break;
        }
      }*/
}

void moveForward(int destination) {
 //destination refers to the amount of grey lines the zumo needs to cross before
 //it gets to its destination.
int start = 0;
while(start < destination){
    if (line_detection() == "LINE") 
    {
      start++; //increment the start variable after it crosses each line
    }
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
motors.setSpeeds(0, 0);
motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
delay(REVERSE_DURATION);
motors.setSpeeds(0, 0);
}

String line_detection() {
if (check_for_wall()){
  return "LINE";
}

  /*  if (sensor_values[0] > QTR_THRESHOLD)
    {
      // if leftmost sensor detects line, reverse and turn to the right
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      delay(REVERSE_DURATION);
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      delay(TURN_DURATION);
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      return "L";
    }
    else if (sensor_values[5] > QTR_THRESHOLD)
    {
      // if rightmost sensor detects line, reverse and turn to the left
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      delay(REVERSE_DURATION);
      motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      delay(TURN_DURATION);
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      return "R";
    }*/
  
  return "N/A";
}


//if sensors other than the far left and right are above the threshold it would indicate we are on a wall. 
  bool check_for_wall() {
  motors.setSpeeds(100, 100);
  reflectanceSensors.read(sensor_values);
  //it's a given one of these values are above the qtr threshold, but we need to check if it's just the left side, or the entire zumo
  if ((sensor_values[0] >= QTR_THRESHOLD) || (sensor_values[5]  >= QTR_THRESHOLD))
  {
    delay(100); //pause the zumo to read the values in again
    reflectanceSensors.read(sensor_values); 
   // if ((sensor_values[1] > QTR_THRESHOLD) || (sensor_values[2] > QTR_THRESHOLD) || (sensor_values[3] > QTR_THRESHOLD) || (sensor_values[4] > QTR_THRESHOLD))
   // { //if any of the middle sensors are above the QTR, stop the zumo. 
       motors.setSpeeds(150, 150);
      delay(200);
      return true;
    // }
  }
  return false;
}

void sensor_callibration() 
{
  
  // Initialise the reflectance sensors module
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);        // turn on LED to indicate we are in calibration mode

  unsigned long startTime = millis();
  while (millis() - startTime < 5000)   // make the calibration take 5 seconds
  {
    //turn left
    motors.setSpeeds(-500, 500);
    delay(2500);
    Serial.println(sensor_values[1]);
    Serial.println(sensor_values[2]);
    Serial.println(sensor_values[3]);
    Serial.println(sensor_values[4]);
    Serial.println(sensor_values[5]);  
    //turn right
    motors.setSpeeds(500, -500);
    delay(2500);
      Serial.println(sensor_values[1]);
    Serial.println(sensor_values[2]);
    Serial.println(sensor_values[3]);
    Serial.println(sensor_values[4]);
    Serial.println(sensor_values[5]);
   
  }
  motors.setLeftSpeed(0); motors.setRightSpeed(0); delay(2);
  digitalWrite(13, LOW);         // turn off LED to indicate we are through with calibration 
}

