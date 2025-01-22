#include "Violin_samples.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>



#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable1;     //xy=121.10000610351562,205
AudioAmplifier           reverb_send;    //xy=199.9889373779297,142.44447326660156
AudioEffectEnvelope      envelope1;      //xy=259.1000061035156,205
AudioEffectFreeverb      freeverb1;      //xy=353.5444755554199,142.111083984375
AudioMixer4              mixer1;         //xy=500.3221740722656,166.88884735107422
AudioAmplifier           amp1;           //xy=628.2110748291016,166.6666717529297
AudioAmplifier           amp2;           //xy=751.2221984863281,166.77777862548828
AudioOutputI2S           i2s1;           //xy=886.0999221801758,166.77775382995605
AudioConnection          patchCord1(wavetable1, envelope1);
AudioConnection          patchCord2(reverb_send, freeverb1);
AudioConnection          patchCord3(envelope1, 0, mixer1, 1);
AudioConnection          patchCord4(envelope1, reverb_send);
AudioConnection          patchCord5(freeverb1, 0, mixer1, 0);
AudioConnection          patchCord6(mixer1, amp1);
AudioConnection          patchCord7(amp1, amp2);
AudioConnection          patchCord8(amp2, 0, i2s1, 0);
AudioConnection          patchCord9(amp2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=236.87777709960938,290.0000228881836
// GUItool: end automatically generated code




float freqnotes[] = {
16.35,      17.32,      18.35,      19.45,      20.60,      21.83,      23.12,      24.50,      25.96,      27.50,      29.14,      30.87, 
32.70,      34.65,      36.71,      38.89,      41.20,      43.65,      46.25,      49.00,      51.91,      55.00,      58.27,      61.74, 
65.41,      69.30,      73.42,      77.78,      82.41,      87.31,      92.50,      98.00,      103.83,     110.00,     116.54,     123.47, 
130.81,     138.59,     146.83,     155.56,     164.81,     174.61,     185.00,     196.00,     207.65,     220.00,     233.08,     246.94, 
261.63,     277.18,     293.66,     311.13,     329.63,     349.23,     369.99,     392.00,     415.30,     440.00,     466.16,     493.88, 
523.25,     554.37,     587.33,     622.25,     659.26,     698.46,     739.99,     783.99,     830.61,     880.00,     932.33,     987.77,       
1046.50,    1108.73,    1174.66,    1244.51,    1318.51,    1396.91,    1479.98,    1567.98,    1661.22,    1760.00,    1864.66,    1975.53, 
2093.00,    2217.46,    2349.32,    2489.02,    2637.02,    2793.83,    2959.96,    3135.96,    3322.44,    3520.00,    3729.31,    3951.07,      
4186.01,    4434.92,    4698.64,    4978.03};

const String noteNames[24]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B","C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

String keyName = "C";
int keyPosition = 0;

int octave = 36;

byte major[] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19};
byte minor[] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19};
byte pentatonic[] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21, 24, 26};
byte majorBlues[] = {0, 2, 3, 4, 7, 9, 12, 14, 15, 16, 19, 21}; 
byte minorBlues[] = {0, 3, 5, 6, 7, 10, 12, 15, 17, 18, 19, 22}; 

byte scale[] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19}; // default to major

float mainVolume = 0.75;

int currentScale = 0;
int numScales = 5;

int currentFunction = 0;
int numFunctions = 3;
const String functionNames[]={"Touch", "Bowing", "Both" };

String scaleTypeName = "Major";

void setupAudio() {

    AudioMemory(20);

    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);

    wavetable1.setInstrument(Violin);

    int wavetableAmplitude = 1;

    wavetable1.amplitude(wavetableAmplitude);

    int attackAmount = 3;
    int releaseAmount  = 1000;

    envelope1.attack(attackAmount);
    envelope1.release(releaseAmount);

    freeverb1.roomsize(0.5);
}

void changeMainVolume() {
    amp2.gain(mainVolume);
}

void playSound(int octave, int note) {
    Serial.println((String)"playSound: Octave = " + octave + " & note = " + note);
    switch(note) 
    {
        case 0:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note]+ octave]);
            envelope1.noteOn();
            break;
        case 1:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 2:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 3:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 4:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 5:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 6:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 7:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 8:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 9:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 10:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
        case 11:
            wavetable1.playFrequency(freqnotes[keyPosition + scale[note] + octave]);
            envelope1.noteOn();
            break;
    }
}

void stopSound(int octave, int note) {
    Serial.println((String)"stopSound: Octave = " + octave + " & note = " + note);
    switch(note) 
    {
        case 0:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 1:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 2:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 3:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 4:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 5:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 6:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 7:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 8:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 9:
            wavetable1.stop();
            envelope1.noteOff();
             break;
        case 10:
            wavetable1.stop();
            envelope1.noteOff();
             break;
        case 11:
            wavetable1.stop();
            envelope1.noteOff();
            break;
    }
}

void changeScale(int scaleType) {
    
    switch(scaleType) {
        case 0: 
            for (uint8_t i=0; i < numberOfSensors; i++) {
                scale[i] = major[i];
            }
            scaleTypeName = "Major";
            break;
        case 1: 
            for (uint8_t i=0; i < numberOfSensors; i++) {
                scale[i] = minor[i];
            }
            scaleTypeName = "Minor";
            break;
        case 2: 
            for (uint8_t i=0; i < numberOfSensors; i++) {
                scale[i] = pentatonic[i];
            }
            scaleTypeName = "Pentatonic";
            break;
        case 3: 
            for (uint8_t i=0; i < numberOfSensors; i++) {
                scale[i] = majorBlues[i];
            }
            scaleTypeName = "Major Blues";
            break;
        case 4: 
            for (uint8_t i=0; i < numberOfSensors; i++) {
                scale[i] = minorBlues[i];
            }
            scaleTypeName = "Minor Blues";
            break;
    }
}



    