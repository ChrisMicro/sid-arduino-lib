/*
 *  Arduino SID simulator amplitude modulation
 *
 *  Hardware Platform: Arduino UNO
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

*/

#include <SID.h>

SID mySid;

void setup()
{
  mySid.begin();

  mySid.setFrequency(0, 440);

  mySid.setWaveForm(0, TRIANGLE);

}

void loop()
{
  int amplitude=0;
  float loopTime=1;
  float samplingTime=0.001;
  float phaseFactor=4*PI*samplingTime/loopTime;

  int counter=0;
  
  while(1)
  {
    for (int n = 0; n < 255; n++)
    {
	  // create a sine wave envelope	
      amplitude = abs(255*sin(n*phaseFactor))+10;
      
	  // set amplitude
      mySid.setAmplitude(0, amplitude);
      
      delay(1);
    }
    
    counter++;
    
	// test a bunch of waveforms
    if(counter>10) mySid.setWaveForm(0, NOISE);
    if(counter>20) mySid.setFrequency(0, 1000);
    if(counter>30) mySid.setFrequency(0, counter*10);
    if(counter>40) mySid.setWaveForm(0, SAWTOOTH);
    if(counter>50) counter=0;
    if(counter==0) 
    {
      loopTime/=2; // increase speed
      phaseFactor=4*PI*samplingTime/loopTime; // increase modulation frequency
      mySid.setWaveForm(0, TRIANGLE);
    }
    
  }


}


