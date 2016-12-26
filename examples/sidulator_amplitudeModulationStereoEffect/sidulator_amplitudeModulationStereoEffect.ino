/*
   Sidulator Synth Stereo

   This is a creative synthesizer where you can controll the the oscillators
   creating stereo sounds with the 3 potientiomets.

   This example especially takes care on creating a 3 dimensional stereo effect.

   Hardware:

   Arduino Nano
   two 100 ohm speaker
   3 buttons
   2 LEDs
   seven segment display
   3 potientiometer


   Dec.2016 ch

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
  int amplitude = 0;
  static float loopTime = 1;
  float samplingTime = 0.001;


  int counter = 0;
  int Channel = 0;
  while (1)
  {
    float phaseFactor = 4 * PI * samplingTime / loopTime;
    float phase = 0;
    for (int n = 0; n < 100; n++)
    {
      // create a sine wave envelope

      amplitude = abs(255 * sin(phase)) + 10;
      phase += phaseFactor;

      // set amplitude
      mySid.setAmplitude(Channel, amplitude);

      delay(1);
    }

    counter++;

    int a = analogRead(A3);
    delay(1);
    int n = Channel;
    if (a < 200)   mySid.setWaveForm(n, TRIANGLE);
    else if (a < 400) mySid.setWaveForm(n, SAWTOOTH);
    else if (a < 600) mySid.setWaveForm(n, RECTANGLE);
    else if (a < 800) mySid.setWaveForm(n, NOISE);

    mySid.setFrequency(n, analogRead(A4));
    delay(1);
    loopTime = (float)analogRead(A2) / 500;
    delay(1);
    Channel++;
    if (Channel > 1)Channel = 0;
  }

}


