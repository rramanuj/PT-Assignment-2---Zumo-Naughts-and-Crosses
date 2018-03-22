#include <ZumoReflectanceSensorArray.h>

#include <Wire.h>
#include <LSM303.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
//LSM303 compass;
#define NUM_SENSORS 6

//NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

#include <Servo.h>

#define CALIBRATION_SAMPLES 70  // Number of compass readings to take when calibrating
#define CRB_REG_M_2_5GAUSS 0x60 // CRB_REG_M value for magnetometer +/-2.5 gauss full scale
#define CRA_REG_M_220HZ 0x1C    // CRA_REG_M value for magnetometer 220 Hz update rate
#define LED_PIN 13
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define BLACK_THRESHOLD 300 // microseconds
#define QTR_THRESHOLD 200   // microseconds

// Speed/duration settings
#define SPEED 150           // Maximum motor speed when going straight; variable speed when turning
#define TURN_BASE_SPEED 100 // Base speed when turning (added to variable speed)

// Allowed deviation (in degrees) relative to target angle that must be achieved before driving straight
#define DEVIATION_THRESHOLD 5
#define REVERSE_SPEED 100
#define TURN_SPEED 150
#define FORWARD_SPEED 100
#define MAX_DISTANCE 30
#define REVERSE_DURATION 250
#define TURN_DURATION 200
LSM303 compass;
Pushbutton button(ZUMO_BUTTON);
//Created a new version of the code which I've tested with the Arduino that works.
ZumoMotors motors;
ZumoReflectanceSensorArray reflectanceSensors(QTR_NO_EMITTER_PIN);
char endDir1;
unsigned int sensor_values[NUM_SENSORS];

#define _COMPLETE 'c'
#define ONE_ONE "ONE_ONE"
#define ONE_TWO "ONE_TWO"
#define ONE_THREE "ONE_THREE"
#define TWO_ONE "TWO_ONE"
#define TWO_TWO "TWO_TWO"
#define TWO_THREE "TWO_THREE"
#define THREE_ONE "THREE_ONE"
#define THREE_TWO "THREE_TWO"
#define THREE_THREE "THREE_THREE"

// Converts x and y components of a vector to a heading in degrees.
// This function is used instead of LSM303::heading() because we don't
// want the acceleration of the Zumo to factor spuriously into the
// tilt compensation that LSM303::heading() performs. This calculation
// assumes that the Zumo is always level.

template <typename T> float heading(LSM303::vector<T> v)
{
  float x_scaled = 2.0 * (float)(v.x - compass.m_min.x) / (compass.m_max.x - compass.m_min.x) - 1.0;
  float y_scaled = 2.0 * (float)(v.y - compass.m_min.y) / (compass.m_max.y - compass.m_min.y) - 1.0;

  float angle = atan2(y_scaled, x_scaled) * 180 / M_PI;
  if (angle < 0)
    angle += 360;
  return angle;
}

void setup()
{
  reflectanceSensors.init();
  reflectanceSensors.calibrate();

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  //Serial.println("asdasdsada...");


  //  initialise_compass();
  button.waitForButton();

  establishContact();

  //sensor_callibration();
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("requestcontact");
    delay(300);
  }
  Serial.read();
}

void loop()
{
  //reflectanceSensors.read(sensor_values);
  //Serial.println(String(sensor_values[0]));
  char command;
  // Serial.println("mary wolsencraft");
  while (command != 'x')
  {
    if (Serial.available() > 0)
    {
      command = Serial.read();
    }
    //Serial.println(command);
    switch (command)
    {
      case 'm': case 'M':
        String message = Serial.readString();
        char dir = message.substring(0, message.indexOf(",")).charAt(0);
        Serial.println(dir);
        string pos = message.substring(message.indexOf(",") + 1, message.lastIndexOf(","));
        Serial.println(pos);
        string dest = message.substring(message.lastIndexOf(",") + 1);
        Serial.println(dest);

        //        char dir = Serial.read();
        //        Serial.println(dir);
        //        float pos = THREE_ONE;
        //        float dest = ONE_ONE;
        bigTing(dir, pos, dest);
    }
  }
}
void moveForward(int destination)
{
  //destination refers to the amount of grey lines the zumo needs to cross before
  //it gets to its destination.
  int start = 0;
  while (start < destination)
  {
    if (line_detection() == "LINE")
    {
      start++; //increment the start variable after it crosses each line
    }
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }

  motors.setSpeeds(0, 0);
  motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
  delay(250);
  motors.setSpeeds(0, 0);
}


void execute()
{
  //placeholder
}

void bigTing(char dir, string pos, string dest)
{
  switch (dir)
  {
    case 'N':
      {
        //northX
        if (pos == ONE_ONE)
        {
          if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == TWO_ONE)
        {
          if (dest == ONE_ONE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_THREE)
        {
          if (dest == ONE_ONE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == THREE_ONE)
        {
          Serial.println("we made it to THREE_ONE");
          if (dest == ONE_ONE)
          {
            Serial.println("we OFGIOASDJHGIDFSAHFIDSAFHUIAEW it to THREE_ONE");
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_TWO)
        {
          if (dest == ONE_ONE)
          {
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_THREE)
        {
          if (dest == ONE_ONE)
          {
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
        }
      }
    case 'S':
      {
        //southX
        if (pos == ONE_ONE)
        {
          if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == TWO_ONE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
        }
        else if (pos == TWO_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == THREE_ONE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
        }
      }
    case 'E':
      {
        //eastX
        if (pos == ONE_ONE)
        {
          if (dest == ONE_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == TWO_ONE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight;
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == THREE_ONE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
        }
      }
    case 'W':
      {
        //westX
        if (pos == ONE_ONE)
        {
          if (dest == ONE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_TWO)
        {
          if (dest == ONE_ONE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == ONE_THREE)
        {
          if (dest == ONE_ONE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == TWO_ONE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == TWO_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateLeft();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'S';
            break;
          }
        }
        else if (pos == THREE_ONE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_TWO)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_TWO)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
          else if (dest == THREE_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_THREE)
          {
            rotateRight();
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'E';
            break;
          }
        }
        else if (pos == THREE_THREE)
        {
          if (dest == ONE_ONE)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_TWO)
          {
            rotateRight();
            moveForward(3);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == ONE_THREE)
          {
            rotateRight();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == TWO_ONE)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_TWO)
          {
            rotateRight();
            moveForward(2);
            execute();
            rotateLeft();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == TWO_THREE)
          {
            rotateRight();
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'N';
            break;
          }
          else if (dest == THREE_ONE)
          {
            moveForward(3);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
          else if (dest == THREE_TWO)
          {
            moveForward(2);
            execute();
            motors.setSpeeds(0, 0);
            endDir1 = 'W';
            break;
          }
        }
      }
      updatePosition(endDir1, dest);
  }
}

void updatePosition(char dir, float pos) {
  Serial.println(_COMPLETE);
  Serial.println(dir);
  Serial.println(pos);
}

String line_detection()
{
  if (check_for_wall())
  {
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
bool check_for_wall()
{
  motors.setSpeeds(100, 100);
  reflectanceSensors.read(sensor_values);
  //it's a given one of these values are above the qtr threshold, but we need to check if it's just the left side, or the entire zumo
  if ((sensor_values[0] >= QTR_THRESHOLD) || (sensor_values[5] >= QTR_THRESHOLD))
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
  digitalWrite(13, HIGH); // turn on LED to indicate we are in calibration mode

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) // make the calibration take 5 seconds
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
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  delay(2);
  digitalWrite(13, LOW); // turn off LED to indicate we are through with calibration
}

void initialise_compass()
{

  // The highest possible magnetic value to read in any direction is 2047
  // The lowest possible magnetic value to read in any direction is -2047
  LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = { -32767, -32767, -32767};
  unsigned char index;

  // Initiate the Wire library and join the I2C bus as a master
  Wire.begin();

  // Initiate LSM303
  compass.init();

  // Enables accelerometer and magnetometer
  compass.enableDefault();

  compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
  compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ);    // 220 Hz compass update rate

  // To calibrate the magnetometer, the Zumo spins to find the max/min
  // magnetic vectors. This information is used to correct for offsets
  // in the magnetometer data.
  motors.setLeftSpeed(SPEED);
  motors.setRightSpeed(-SPEED);

  for (index = 0; index < CALIBRATION_SAMPLES; index++)
  {

    // Take a reading of the magnetic vector and store it in compass.m
    compass.read();

    running_min.x = min(running_min.x, compass.m.x);
    running_min.y = min(running_min.y, compass.m.y);

    running_max.x = max(running_max.x, compass.m.x);
    running_max.y = max(running_max.y, compass.m.y);
    delay(50);
  }

  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);

  // Set calibrated values to compass.m_max and compass.m_min
  compass.m_max.x = running_max.x;
  compass.m_max.y = running_max.y;
  compass.m_min.x = running_min.x;
  compass.m_min.y = running_min.y;
}

// Average 10 vectors to get a better measurement and help smooth out
// the motors' magnetic interference.
float averageHeading()
{
  LSM303::vector<int32_t> avg = {0, 0, 0};

  for (int i = 0; i < 10; i++)
  {
    compass.read();
    avg.x += compass.m.x;
    avg.y += compass.m.y;
  }
  avg.x /= 10.0;
  avg.y /= 10.0;

  // avg is the average measure of the magnetic vector.
  return heading(avg);
}

float relativeHeading(float heading_from, float heading_to)
{
  float relative_heading = heading_to - heading_from;

  // constrain to -180 to 180 degree range
  if (relative_heading > 180)
    relative_heading -= 360;
  if (relative_heading < -180)
    relative_heading += 360;
  return relative_heading;
}

void rotateRight()
{
  rotate(fmod(averageHeading() + 90, 360));
}

void rotateLeft()
{
  rotate(fmod(averageHeading() - 80, 360));
}

//this function rotates the zumo based on degrees passed in by the user (i.e. 90)
//this was heavily inspired from the compass example
void rotate(int degrees) //rotate to an angle based on compass
{
  int speed;
  float heading = averageHeading();
  float relative = relativeHeading(heading, degrees);
  while (abs(relative) > DEVIATION_THRESHOLD)
  {
    heading = averageHeading();
    relative = relativeHeading(heading, degrees);
    speed = SPEED * relative / 180;
    if (speed < 0)
      speed -= TURN_BASE_SPEED;
    else
      speed += TURN_BASE_SPEED;
    motors.setSpeeds(speed, -speed);
  }
  motors.setSpeeds(0, 0);
  delay(400);
}