void printDirectory(File dir) 
{
  dir.rewindDirectory();
  while(true)
  {
    File entry = dir.openNextFile();
    if (! entry) 
    {
      return;
    }
    if( ! entry.isDirectory())
    {
      bool test =  isWaveFile(entry);
      //add the file to the array;
    }
    entry.close();
  }
}

int numberOfWavFilesInDirectory(File dir)
{
  dir.rewindDirectory();
  int i = 0; 
  while(true)
  {
    File entry = dir.openNextFile();
    if (! entry) 
    {
      Serial.print("I count ");
      Serial.print(i);
      Serial.println(" WAV files");
      return i;
    }
    if( ! entry.isDirectory())
    {
      if( isWaveFile(entry))
      {
        i++;
      }
    }
    entry.close();
  }
}

bool isWaveFile(File file)
{
  String name = file.name();
  //Serial.print(file.name());
  if  (name.endsWith(".WAV"))
  {
    if(name.indexOf("~") < 0)
    {
      //Serial.println(" is WAV");
      return true;
    }
  }
  //Serial.println(" is not WAV ");
  return false;
}

void fillArrayOfWavFilesWithDir(File dir)
{  
  int fileIndex = 0;
  File file;
  for (int i = 0 ; i < MAX_NUMBER_OF_WAV_FILES ; i ++)
  {

    audioFiles[i] = file;
  }

  dir.rewindDirectory();
  while(true)
  {
    File entry = dir.openNextFile();
    if (! entry) 
    {
      return;
    }
    if( ! entry.isDirectory())
    {
      if( isWaveFile(entry))
      {
        audioFiles[fileIndex] = entry;
        fileIndex++;
      }
    }
    entry.close();
  }
}

void printFileArray()
{
  for (int i = 0 ; i < MAX_NUMBER_OF_WAV_FILES ; i ++)
  {
    File f = audioFiles[i] ;
    String name = f.name();
    if(name.length() >0)
    {
      Serial.println(f.name());
    }
  }
}











