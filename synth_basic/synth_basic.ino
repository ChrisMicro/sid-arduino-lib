/*
 * Arduino SID simple sound
 * 
 */
 
#include <SID.h>

SID mySid;

void setup() 
{
  mySid.begin();

}

void loop() 
{
  mySid.setFrequency(0,440);

  mySid.setWaveForm(0,TRIANGLE);
  
  mySid.noteOn(0);
  delay(100);
  mySid.noteOff(0);
  delay(400);  

  mySid.setWaveForm(0,SAWTOOTH);
  
  mySid.noteOn(0);
  delay(100);
  mySid.noteOff(0);
  delay(400);  

  mySid.setWaveForm(0,RECTANGLE);
  mySid.setPWM(0,256/4);

  mySid.noteOn(0);
  delay(100);
  mySid.noteOff(0);
  delay(400);  
    
  mySid.setWaveForm(0,NOISE);
  
  mySid.noteOn(0);
  delay(100);
  mySid.noteOff(0);
  delay(400);  
}


