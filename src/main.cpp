#include <Arduino.h>

/*
Use standard address is tied to Ground which gives the default address of 0x5A

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/


#include "constants.h"
#include "synth_wavetable.h"
#include "touch.h"
#include "wavetable.h"
#include "reboot.h"
#include "encoderFile.h"
#include "joystick.h"
#include "drawMenu.h"

void setup() {
  Serial.begin(9600);
  init_mpr121();
  setupJoystick();
  // setupPins();
  u8g2.begin();
  drawMenu();
  setupAudio();
  pinMode(rebootButton, INPUT_PULLUP);
  pinMode(volumePin, INPUT);
  delay(500);
}

void touchRelease() {
  for (int i = 0; i < 12; i++) {
    if (MPR121.isNewRelease(i)) {
      stopSound(octave, i);
    }
  }
}


void loop() {

  readJoystick();
  joyStickActions();

  MPR121.updateAll();

  for (int i = 0; i < 12; i++) {
    if (MPR121.isNewTouch(i)) {
      playSound(octave, i);
    }
  }

  // currentFunction 0 = Touch, 1 = Bowing, 2 = Both

  switch (currentFunction)
  {
  case 0:
    gain = 1;
    rampVolume();
    touchRelease();
    break;
  case 1:
    readBowing();
    rampVolume();
    break;
  case 2:
    touchRelease();
    readBowing();
    rampVolume();
  }

  if (updateDisplayFlag == true) {
        drawMenu();            
        updateDisplayFlag = false;
    }

  if(digitalRead(rebootButton) == LOW){
      doReboot();
  }

  Serial.print("volume: ");
  Serial.println(gain);

}


