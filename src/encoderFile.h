#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(14, 15);
//   avoid using pins with LEDs attached

long oldPosition  = 0;
unsigned long readBowTime = millis();
unsigned long timingResolution = 100;
bool direction = 0;
unsigned long lastChange = millis();
bool change = 0;
long sensorSensitivity = 2;

unsigned long fast = 200; // so if this or faster then highest volume
// unsigned long medium = 800; // inbetween it would be cool to have the volume changing between those two extremes, mapped to where in between it was
unsigned long slow = 2000; // and if this or lower then lowest volume
unsigned long off = 3500;

unsigned long volumeRampTime = millis();
unsigned long volumeRampResolution = 5;
float gain = 0;
float bowVolume = 0;


void changeVolume(float volume) {
  bowVolume = volume;
}

void rampVolume() {
  unsigned long timeNow = millis();
  unsigned long timeElapsed = timeNow - volumeRampTime;
  
  if (timeElapsed > volumeRampResolution) {
    if (bowVolume == gain) {
      return;
    }
    if (bowVolume < gain) {
      gain = gain - 0.01;
    } else if (bowVolume > gain) {
      gain = gain + 0.01;
    }

    // Serial.println(gain);
    
    amp1.gain(gain);

    volumeRampTime = timeNow;
  }

}


void changeTime() {
  unsigned long timeNow = millis();
  unsigned long timeElapsed = timeNow - lastChange;

 if (timeElapsed > slow) {
    Serial.println("slowchange");
    changeVolume(0.2);
  } else if (timeElapsed > fast) {
    Serial.println("medium change!");
    int volume = map(timeElapsed, fast, slow, 0, 80);
    volume = 100 - volume;
    float volumeConverted = volume;
    volumeConverted = volumeConverted/100;
    Serial.println(volumeConverted);
    changeVolume(volumeConverted);
  } else {
    Serial.println("fast change!");
    changeVolume(1);
  }

  lastChange = timeNow;
}

void readBowingDirection() {
  long newPosition = myEnc.read();
  unsigned long timeNow = millis();
  bool checkChange = 0;
  
  if (timeNow - readBowTime > timingResolution) { // if it's been longer than timing resolution

    long distanceTravelled = newPosition - oldPosition; // read the sensor and call the answer distance travelled
  if (distanceTravelled == 0){
        changeVolume(0);
  }

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

    if (timeNow - lastChange > off) {
    // Serial.println("off");
      changeVolume(0);
    }

    if (change) {
      // Serial.println("Change!!!");
      changeTime();
    }
    
    oldPosition = newPosition;
    readBowTime = millis();
  }
}

void readBowing() {
  readBowingDirection();
}