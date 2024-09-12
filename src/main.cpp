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
#include "encoder.h"
#include "drawMenu.h"


// float gain = 0;

#define UP 0
#define LEFT 1
#define CENTRE 2
#define RIGHT 3
#define DOWN 4
#define NUM_BUTTONS 5





void setup() {
Serial.begin(9600);
init_mpr121();
// setupPins();
u8g2.begin();
drawMenu();
setupAudio();
pinMode(rebootButton, INPUT_PULLUP);
pinMode(volumePin, INPUT);
delay(500);
}


void loop() {
// ***** uncomment for volume control

// int knob = analogRead(volumePin) - 200; // knob = 0 to 1023
// float gain = (float)knob / 1023.0;
// Serial.print("Gain is: ");
// Serial.println(gain);

// ***** if no software volume control then set gain

rampVolume();

// currtouched1 = mprBoard_A.touched();

if(digitalRead(rebootButton) == LOW){
    doReboot();
}

// for (uint8_t i=0; i < numberOfSensors; i++) {
//       if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
//       playSound(octave, i);
//       }

//       if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
//       stopSound(octave, i);
//     }
//   }

// lasttouched1 = currtouched1;

MPR121.updateAll();

  for (int i = 0; i < 12; i++) {
    if (MPR121.isNewTouch(i)) {
      Serial.print("electrode ");
      Serial.print(i, DEC);
      Serial.println(" was just touched");
      playSound(octave, i);

    } else if (MPR121.isNewRelease(i)) {
      Serial.print("electrode ");
      Serial.print(i, DEC);
      Serial.println(" was just released");
      stopSound(octave, i);

    }
  }

readBowing();

 if (updateDisplayFlag == true) {
      drawMenu();            //update the menu
      updateDisplayFlag = false;
  }


return;
}


