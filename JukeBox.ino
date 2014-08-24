#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

AudioPlaySdWav     wav;
AudioOutputI2S     dac;
AudioConnection c1(wav, 0, dac, 0);
AudioConnection c2(wav, 1, dac, 1);
AudioControlSGTL5000 audioShield;

#define MAX_NUMBER_OF_WAV_FILES 100
File root;
File audioFiles[MAX_NUMBER_OF_WAV_FILES] ;
int numberOfWavFile = 0;



void setup()
{
  AudioMemory(200);
  audioShield.enable();
  SPI.setMOSI(7);
  SPI.setSCK(14);
  SD.begin(10);
  root = SD.open("/");
  numberOfWavFile = numberOfWavFilesInDirectory(root);
  fillArrayOfWavFilesWithDir(root);
  printFileArray();
  playFileAtIndex(2);
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

void playFileAtIndex(int index)
{    
  Serial.print("Playing : ");
  File f = audioFiles[index];
  String fName = f.name();
  char buf [fName.length()+1];
  fName.toCharArray(buf, fName.length()+1) ;
  Serial.println(buf);
  wav.play(buf);

}













