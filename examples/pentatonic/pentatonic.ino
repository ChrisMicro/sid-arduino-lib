/*
 * Arduino SID simulator meditave music
 * 
 * original version: Jeremy Fonte
 * addapted and corrected for the sid library
 * 2016 ch
 * 
 * Hardware Platform: Arduino UNO
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

void playSound(long frequency, long length) 
{
  mySid.setFrequency(0,frequency);
  
  mySid.noteOn(0);
  delay(length/10);
  mySid.noteOff(0);
  delay(50);
}

// http://fonte.me/arduino/#Musician
/*
 Musician
Plays a (fairly) random tune until the program is stopped
8-ohm speaker on digital pin 8
//Copyright (c) 2012 Jeremy Fonte
//This code is released under the MIT license
//http://opensource.org/licenses/MIT
*/

int randomNote = 131;
int randomDuration = 2;
int noteStep = 1;
int notes[16];

void setup() 
{
  mySid.begin();
  mySid.set_register(ATTACKDECAY+VOICE1,FASTATTACK+SLOWDECAY); 
  mySid.set_register(SUSTAINRELEASE+VOICE1,SUSTAINNORM+5);

  mySid.setWaveForm(0,TRIANGLE);

  notes[1] = 131;
  notes[2] = 147;
  notes[3] = 165;
  notes[4] = 196;
  notes[5] = 220;
  notes[6] = 262;
  notes[7] = 294;
  notes[8] = 330;
  notes[9] = 392;
  notes[10] = 440;
  notes[11] = 523;
  notes[12] = 587;
  notes[13] = 659;
  notes[14] = 784;
  notes[15] = 880;

  randomNote = random(1, 15);
}

void loop() {

  static uint8_t count = 0;

 // setLed(EYE_LED_LEFT,  !((count) & 01));
 // setLed(EYE_LED_RIGHT, (count) & 01);
  count++;

  noteStep = random(-3, 3);
  randomNote = randomNote + noteStep;
  if (randomNote < 1) {
    randomNote = random(1, 15);
  }
  else if (randomNote > 15) {
    randomNote = random(1, 15);
  }

  randomDuration = random(1, 8);
  // to calculate the note duration, take one second
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 3000 / randomDuration;
  //tone(8, notes[randomNote],noteDuration);
  
  playSound( notes[randomNote], noteDuration);

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(10);
  // stop the tone playing:
  //noTone(8);
}

