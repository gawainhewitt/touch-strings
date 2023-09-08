/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Testing:");
}

long oldPosition  = 0;
bool playing = false;
int bowingSensitivity = 5;
unsigned long myTime = millis();
int timingResolution = 100;
int quiet = 100;
int medium = 500;
int loud = 1000;

void loop() {
  long newPosition = myEnc.read();
  unsigned long timeNow = millis();
  
  if (timeNow - myTime > timingResolution) {

    long distanceTravelled = newPosition - oldPosition;

    if (distanceTravelled < 0) {
      distanceTravelled = distanceTravelled * -1;
    }
    // Serial.println(distanceTravelled);
    
    if (distanceTravelled > bowingSensitivity) {
      if (distanceTravelled < medium) {
        Serial.println("quiet");
      } else if (distanceTravelled < loud) {
        Serial.println("medium");
      } else {
        Serial.println("loud");
      }
      // Serial.print("new position = ");
      // Serial.println(newPosition);
      // Serial.print("x travel = ");
      // Serial.println(newPosition - oldPosition);
      myTime = millis();
      oldPosition = newPosition;

      if (!playing) {
        playing = true;
        Serial.println("playing");
      }
    } else {
      if (playing) {
          playing = false;
          Serial.println("stopped");
        }
    }
  }
}