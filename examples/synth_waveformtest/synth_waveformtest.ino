/*
 * Arduino SID simulator waveform demonstration
 * 
 * Hardware Platform: Arduino UNO
 * 
 * sound outputs: Pin9
 * 
 * This are PWM-outputs. To improve sound quality connect a RC-low pass filter between Audio jack
 * 
 * Mono Operation:
 * 
 * PIN9  --- 1K ---|
 *                 o---------------> Audio Jack
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

void setup() 
{
  mySid.begin();

  // set ADSR envelope
  // https://en.wikipedia.org/wiki/Synthesizer#Attack_Decay_Sustain_Release_.28ADSR.29_envelope
  // uint8_t voiceNumber,uint16_t attack_ms, uint16_t decay_ms, uint8_t sustain_level, uint16_t release_ms
  mySid.setADSR(0,10,1,200,200); 
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


