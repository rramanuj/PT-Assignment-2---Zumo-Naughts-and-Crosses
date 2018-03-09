//StandardCplusplus library from GitHub
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>
//other libraries
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
using namespace std;

// -- GLOBALS -- //
int crosses_x, crosses_y, naughts_x, naughts_y;

// -- CONSTANTS -- //
//pin values
#define LED_PIN 13
#define TRIGGER_PIN 2
#define ECHO_PIN 6

//possible commands received from GUI
#define _ONE 1
#define _TWO 2
#define _THREE 3

//constant strings to pass back to GUI
#define EDGE_REACHED "Edge of track detected - turn required"
#define EDGE_REACHED_LEFT_ONLY "Back to sub corridor entrance - turn left to continue"
#define EDGE_REACHED_RIGHT_ONLY "Back to sub corridor entrance - turn right to continue"
#define OBJECT_DETECTED "Object detected in room "
#define OBJECT_NOT_DETECTED "No objects detected in room "
#define INVALID_COMMAND "Invalid command! That command cannot be used at this time"

//sensitivity to border
#define QTR_THRESHOLD  300
//speed
#define REVERSE_SPEED     100
#define TURN_SPEED        100
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200
#define TURN_DURATION     300
//delay times
#define DELAY_CONTACT 300
#define DELAY_PAUSE 50
#define DELAY_COMMAND 2

//number of sensors on Zumo
#define NUM_SENSORS 6

//initialise sensor object
ZumoMotors motors;
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
// -- CONSTANTS -- //

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initialise_compass() {

  // The highest possible magnetic value to read in any direction is 2047
  // The lowest possible magnetic value to read in any direction is -2047
  LSM303::vector<int16_t> running_min = { 32767, 32767, 32767 }, running_max = { -32767, -32767, -32767 };
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
  LSM303::vector<int32_t> avg = { 0, 0, 0 };

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
