#include <Arduino.h>

/*
Use standard address is tied to Ground which gives the default address of 0x5A

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "synth_wavetable.h"
#include "mpr121.h"
#include "wavetable.h"
#include "reboot.h"
#include "encoder.h"

void setup() {
Serial.begin(9600);
init_mpr121();
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

amp1.gain(gain);

currtouched1 = mprBoard_A.touched();

if(digitalRead(rebootButton) == LOW){
    doReboot();
}

for (uint8_t i=0; i < numberOfSensors; i++) {
      if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      playSound(octave, i);
      }

      if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      stopSound(octave, i);
    }
  }

lasttouched1 = currtouched1;

readBowing();

return;
}


