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
int sensitivity = 5;
unsigned long myTime = millis();
int checkTime = 100;

void loop() {
  long newPosition = myEnc.read();
  unsigned long timeNow = millis();
  
  if (timeNow - myTime > checkTime) {
    
    if (newPosition > (oldPosition + sensitivity) || newPosition < (oldPosition - sensitivity)) {
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