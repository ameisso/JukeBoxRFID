#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

AudioPlaySdWav     wav;
AudioOutputI2S     dac;

AudioConnection c1(wav, 0, dac, 0);
AudioConnection c2(wav, 1, dac, 1);

AudioControlSGTL5000 audioShield;

File root;

void setup()
{


  AudioMemory(200);

  audioShield.enable();
  audioShield.volume(0.9);

  SPI.setMOSI(7);
  SPI.setSCK(14);
  if (SD.begin(10)) {
    // wav.play("testt.wav");
  }
      root = SD.open("/");
    printDirectory(root, 0);

  audioShield.volume(0.3);


}

void loop() 
{
  updateVolume();
  delay(20);
}

void updateVolume()
{
  float vol = analogRead(15);
  vol = vol / 1024;
  audioShield.volume(vol);
}

void printDirectory(File dir, int numTabs) 
{
  dir.rewindDirectory();
for (int i = 0; i< 10; i++)
  {
    File entry = dir.openNextFile();
    if (! entry) {
      // no more files
      //Serial.println("**nomorefiles**");
      break;
    }
    for (uint8_t i=0; i<numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      //Serial.println("/");
      //printDirectory(entry, numTabs+1);
    }
    else {
      // files have sizes, directories do not
      //Serial.print("\t\t");
      //Serial.println(entry.size(), DEC);
      Serial.println();
    }
    // Make sure to close everything that we open when we are done with it
    entry.close();
  }
}



