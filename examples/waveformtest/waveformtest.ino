/*
 * Arduino SID simulator demonstration
 * 
 * Hardware Platform: Arduino UNO
 * 
 * sound outputs: Pin9, pin10
 * 
 * This are PWM-outputs. To improve sound quality connect a RC-low pass filter between Audio jack
 * 
 * Mono Operation:
 * 
 * PIN9  --- 1K ---|
 * PIN10 --- 1K ---o---------------> Audio Jack
 *                 |
 *                --- 100 nF    
 *                ---
 *                 |
 *                 |
 *                GND
 * 
 * 
 */
 
#include <SID.h>

SID mySid;

#define SLOWATTACK 0xB0
#define FASTATTACK 0x00
#define SLOWDECAY 0x0A
#define FASTDECAY 0x00
#define SUSTAINQUITE 0x00
#define SUSTAINNORM  0xA0
#define SUSTAINLOUD 0xF0
#define SLOWRELEASE 0x09
#define FASTRELEASE 0x00

void setup() 
{
  mySid.begin();
  mySid.set_register(ATTACKDECAY+VOICE1,FASTATTACK+SLOWDECAY); 
  mySid.set_register(SUSTAINRELEASE+VOICE1,SUSTAINNORM+5);
}

void loop() 
{
  int a=analogRead(0);
 
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


