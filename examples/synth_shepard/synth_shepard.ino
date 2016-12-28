/*
 * Arduino SID simple triangle sound
 * 
 * 
 * Is it possible to create a Shepard tone with oscillators?
 * 
 * https://en.wikipedia.org/wiki/Shepard_tone
 * 
 */
 
#include <SID.h>

SID mySid;

int f1=440;
int f2;
int f3;

void setup() 
{
  mySid.begin();

  f2=3*f1;
  f3=6*f1;
  int waveform=RECTANGLE;
  //configure channel 0
  mySid.setFrequency(0,f1);
  mySid.setWaveForm(0,waveform);
  mySid.setAmplitude(0,250);

  mySid.setFrequency(1,f2);
  mySid.setWaveForm(1,waveform);
  mySid.setAmplitude(1,250);

  mySid.setFrequency(2,f3);
  mySid.setWaveForm(2,waveform);
  mySid.setAmplitude(2,250);

}

void loop() 
{
  f1++;
  if(f1>4000) f1=300;
  f2++;
  if(f2>4000) f2=300;
  f3++;
  if(f3>4000) f3=300;
  
  mySid.setFrequency(0,f1);
  mySid.setFrequency(1,f2);
  mySid.setFrequency(2,f3);
  delay(10);
  

}


