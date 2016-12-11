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
  mySid.setWaveForm(0,TRIANGLE);
}

/*
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM
  by: Dipto Pratyaksa
  last updated: 31/3/13

  from:
  http://www.linuxcircle.com/2013/03/31/playing-mario-bros-tune-with-arduino-and-piezo-buzzer/

*/
#include "pitches.h"

#define melodyPin 9 // this is not used for the SID

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
int song = 0;

void buzz(int targetPin, long frequency, long length) 
{
  mySid.setFrequency(0,frequency);
  
  mySid.noteOn(0);
  delay(50);
  mySid.noteOff(0);
  delay(length*2-50);  
}

void sing(int s){      
   // iterate over the notes of the melody:
   song = s;
   if(song==2){
     //Serial.println(" 'Underworld Theme'");
     int size = sizeof(underworld_melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/underworld_tempo[thisNote];

       buzz(melodyPin, underworld_melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       //int pauseBetweenNotes = noteDuration * 1.30;
       //delay(pauseBetweenNotes);

       // stop the tone playing:
       //buzz(melodyPin, 0,noteDuration);

    }

   }else{

     //Serial.println(" 'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       //int pauseBetweenNotes = noteDuration * 1.30;
       //delay(pauseBetweenNotes);

       // stop the tone playing:
       //buzz(melodyPin, 0,noteDuration);

    }
  }
}


void loop()
{
  mySid.setWaveForm(0,TRIANGLE);
  sing(2);

  mySid.setFrequency(0,440);
  mySid.setWaveForm(0,NOISE);
  mySid.noteOn(0);
  delay(100);
  mySid.noteOff(0);
  delay(3000); 
}






