#include <Audio.h>
// #include <Wire.h> // already in mpr121.h
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int numberOfSensors = 7;
const int allSensorsBehaveAsOne = 1; // if this number is 1 then all sensors will behave as one. If it is number of sensors then each is assigned its own file and is independant
int numberOfFiles = 0;

String sdContents[200];
String soundUsed[200];

String mySounds[allSensorsBehaveAsOne]; 

String name = "000.wav";

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=250,98
AudioEffectEnvelope      envelope1;      //xy=634,146
AudioEffectEnvelope      envelope2;      //xy=664,288
AudioAmplifier           amp1;           //xy=966,318
AudioAmplifier           amp2;           //xy=973,412
AudioOutputI2S           i2s1;           //xy=1094,556
AudioConnection          patchCord1(playSdWav1, 0, envelope1, 0);
AudioConnection          patchCord2(playSdWav1, 1, envelope2, 0);
AudioConnection          patchCord3(envelope1, amp1);
AudioConnection          patchCord4(envelope2, amp2);
AudioConnection          patchCord5(amp1, 0, i2s1, 0);
AudioConnection          patchCord6(amp2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=841,659
// GUItool: end automatically generated code


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

int countDirectory(File dir) {
  int count_files = 0;
    while(true) {
      File entry = dir.openNextFile();
      if (! entry) {
        Serial.println("no more files");
        return count_files;
        break;
      }
      String file_name = entry.name();	//Get file name so that we can check 
      if(file_name[4] == 'w'){
        Serial.println(file_name);
        sdContents[count_files] = file_name;
        count_files += 1;
      }
    }
}

// void init_player() {

//   // Audio connections require memory to work.  For more
//   // detailed information, see the MemoryAndCpuUsage example
//   AudioMemory(8);

//   // Comment these out if not using the audio adaptor board.
//   // This may wait forever if the SDA & SCL pins lack
//   // pullup resistors
//   sgtl5000_1.enable();
//   sgtl5000_1.volume(0.5);

//   SPI.setMOSI(SDCARD_MOSI_PIN);
//   SPI.setSCK(SDCARD_SCK_PIN);
//   if (!(SD.begin(SDCARD_CS_PIN))) {
//     // stop here, but print a message repetitively
//     while (1) {
//       Serial.println("Unable to access the SD card");
//       delay(500);
//     }
//   }

//   File root = SD.open("/");
  
//   numberOfFiles = countDirectory(root);

//   Serial.print("number of files = ");
//   Serial.println(numberOfFiles);

//   for(int i = 0; i < numberOfFiles; i++){
//     Serial.print("sdContent = ");
//     Serial.println(sdContents[i]);
//     soundUsed[i] = sdContents[i];
//   }

//   for(int i = 0; i < allSensorsBehaveAsOne; i++){
//     mySounds[i] = sdContents[i];
//     soundUsed[i] = "true";
//   }

// }

// // Map of which voice has which key playing
// int active[MAX_POLY];
// // Map of when each voice started playing, for note stealing
// long when[MAX_POLY];
// // Map of when we started the fade out so we know when to kill the note after the fade
// long faded_ms[MAX_POLY];

// void changeSound(int track) {
//   bool reload = false;
//   if(soundUsed[numberOfFiles-1] == "true"){
//     for(int i = 0; i < numberOfFiles; i++){
//       soundUsed[i] = sdContents[i];
//     }
//   }
//   for(int i = 0; i < numberOfFiles; i++){
//     Serial.print("soundUsed = ");
//     Serial.println(soundUsed[i]);
//     if(soundUsed[i] != "true"){
//       mySounds[track] = sdContents[i];
//       soundUsed[i] = "true";
//       return;
//     }
//   }
// }

void playSound(int track) {
  // playSdWav1.play(mySounds[0].c_str());
  // envelope1.noteOn();
  // envelope2.noteOn();
  // changeSound(0);
}

