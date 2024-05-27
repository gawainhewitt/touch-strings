#include <Arduino.h>

/*
Use standard address is tied to Ground which gives the default address of 0x5A

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "mpr121.h"
#include "wavFilePlayer.h"
#include "reboot.h"

void setup() {
Serial.begin(9600);
init_mpr121();
// init_player();
pinMode(rebootButton, INPUT_PULLUP);
pinMode(volumePin, INPUT);
delay(500);
envelope1.attack(4000);
envelope2.attack(4000);
envelope1.hold(0);
envelope1.hold(0);
}


void loop() {
// ***** uncomment for volume control

int knob = analogRead(volumePin) - 200; // knob = 0 to 1023
float gain = (float)knob / 1023.0;
// Serial.print("Gain is: ");
// Serial.println(gain);

// ***** if no software volume control then set gain

// float gain = 1.0;

amp1.gain(gain);
amp2.gain(gain);
envelope1.sustain(1);
envelope2.sustain(1);

currtouched1 = mprBoard_A.touched();

if(digitalRead(rebootButton) == LOW){
    doReboot();
}

//For A----------------------------------------------------------
for (uint8_t i=0; i < numberOfSensors; i++) {
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
    Serial.print(i); Serial.println(" touched of A");
    // playSound(i);
    }
}

lasttouched1 = currtouched1;
return;
}
