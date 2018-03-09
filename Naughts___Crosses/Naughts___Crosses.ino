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
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.begin(9601);
  establishContact(9600);
  establishContact(9601);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("requestcontact");
    delay(DELAY_CONTACT);
  }
  Serial.read();
}
