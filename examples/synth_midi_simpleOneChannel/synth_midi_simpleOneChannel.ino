/*
    very simple midi player
    has only one channel and one note

    Hardware:
    Arduino UNO

    Pin 0 ( RXD ) connecte to MIDI signal from Keyboard
    PIN 9 PWM Audio Output

    Dec.2016 ch
*/

#include <SID.h>
#include "pitches.h"

SID mySid;

#define LED0 13
#define TESTPIN 2

void setup() {

  Serial.begin(31250);
  pinMode(LED0, OUTPUT);
  pinMode(TESTPIN, OUTPUT);

  digitalWrite(LED0, 1); // led on

  mySid.begin();

  // set ADSR envelope
  mySid.setADSR(0, 10, 1, 200, 200);

  mySid.setWaveForm(0, TRIANGLE);

  // test tone
  mySid.setFrequency(0, 440);
  mySid.noteOn(0);
  delay(1000);
  mySid.noteOff(0);
}

#define KEEP_ALLIVE_MESSAGE 0xFE



uint8_t midiGetByte()
{
  uint8_t c;
  while (!Serial.available()); // wait for input
  c = Serial.read();

  return c;
}

void toggleLed0()
{
  static uint8_t flag = true;
  if (flag)digitalWrite(LED0, 0);
  else digitalWrite(LED0, 1);;
  flag = !flag;
}

//Midi command lengths
//8,9,a,b,c,d,e,f
uint8_t bytes2read[] = {2, 2, 2, 2, 1, 1, 2, 1};

void loop()
{
  static uint8_t midiState = 0;
  uint8_t kk, vv;
  uint16_t frequency = 0;

  kk = midiGetByte();

  // toggle the led if controller is connected and sends its alive messages
  if ( kk == KEEP_ALLIVE_MESSAGE)
  {
    static uint8_t counter = 0;
    counter++;
    if (counter > 10)
    {
      toggleLed0();
      counter = 0;
    }
  }
  else
  {
    // send debug pulse for use with logic analyser
    digitalWrite(TESTPIN, 1);
    digitalWrite(TESTPIN, 0);

    if (kk & 0x80 ) // state?
    {
      midiState = kk & 0xF0;
      kk = midiGetByte();
    }

    if ( bytes2read[ (midiState >> 4) - 8 ] == 2) vv = midiGetByte();

    if ( midiState == 0x80) // note off
    {
      mySid.noteOff(0);
    }

    if ( midiState  == 0x90) // note on
    {
      if (vv == 0) // 0 is defined as noteOff
      {
        mySid.noteOff(0);
      }
      else
      {
        frequency = sNotePitches[kk];
        mySid.setFrequency(0, frequency);
        mySid.noteOn(0);
      }
    }

    if ( midiState == 0xA0)
    {
    }

    if ( midiState == 0xB0)
    {
    }

    if ( midiState   == 0xC0) // program change ( new instrument )
    {
      kk&=3;
      if(kk==0) mySid.setWaveForm(0, TRIANGLE);
      if(kk==1) mySid.setWaveForm(0, SAWTOOTH);
      if(kk==2) mySid.setWaveForm(0, RECTANGLE);
      if(kk==3) mySid.setWaveForm(0, NOISE);
    }
    
    if ( midiState  == 0xD0)
    {
    }

    if ( midiState  == 0xE0)
    {
    }

    if ( midiState  == 0xF0)
    {
    }
  }
}
