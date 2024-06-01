#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(14, 15);
//   avoid using pins with LEDs attached

long oldPosition  = 0;
bool playing = false;
int bowingSensitivity = 5;
unsigned long myTime = millis();
unsigned long timingResolution = 100;
int quiet = 100;
int medium = 500;
int loud = 1000;

void readBowing() {
  long newPosition = myEnc.read();
  unsigned long timeNow = millis();
  
  if (timeNow - myTime > timingResolution) {

    long distanceTravelled = newPosition - oldPosition;

    if (distanceTravelled < 0) {
      distanceTravelled = distanceTravelled * -1;
    }
    Serial.println(distanceTravelled);
    oldPosition = newPosition;
    myTime = millis();

    // if (distanceTravelled > bowingSensitivity) {
    //   if (distanceTravelled < medium) {
    //     Serial.println("quiet");
    //   } else if (distanceTravelled < loud) {
    //     Serial.println("medium");
    //   } else {
    //     Serial.println("loud");
    //   }
      
    //   myTime = millis();
    //   oldPosition = newPosition;

    //   if (!playing) {
    //     playing = true;
    //     Serial.println("playing");
    //   }
    // } else {
    //   if (playing) {
    //       playing = false;
    //       Serial.println("stopped");
    //     }
    // }
  }
}