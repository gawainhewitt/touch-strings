#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(14, 15);
//   avoid using pins with LEDs attached

long oldPosition  = 0;
unsigned long myTime = millis();
unsigned long timingResolution = 100;
bool direction = 0;
bool change = 0;
long sensorSensitivity = 2;

void readBowingDirection() {
  long newPosition = myEnc.read();
  unsigned long timeNow = millis();
  bool checkChange = 0;
  
  if (timeNow - myTime > timingResolution) { // if it's been longer than timing resolution

    long distanceTravelled = newPosition - oldPosition; // read the sensor and call the answer distance travelled

    // Serial.println((String) "distance travelled " + distanceTravelled);

    if (direction == 1) {
      if (distanceTravelled < 0 - sensorSensitivity) {
        direction = 0;
        checkChange = 1;
      } else if (distanceTravelled > 0 + sensorSensitivity) {
        checkChange = 0;
      }
    } else {
      if (distanceTravelled > 0 + sensorSensitivity) {
        direction = 1;
        checkChange = 1;
      } else if (distanceTravelled < 0 - sensorSensitivity) {
        checkChange = 0;
      }
    }

    if (checkChange != change) {
      // Serial.println((String) "change " + checkChange);
      // Serial.println((String) "direction " + direction);
      change = checkChange;
    }

    if (change) {
      Serial.println("Change!!!");
    }
    
    oldPosition = newPosition;
    myTime = millis();
  }
}