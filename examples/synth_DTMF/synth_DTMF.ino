 /*
 * Arduino SID DUAL TONE Dialing
 * https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling
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

int DTMF[13][2]={
  {941,1336}, // frequencies for touch tone 0
  {697,1209}, // frequencies for touch tone 1
  {697,1336}, // frequencies for touch tone 2
  {697,1477}, // frequencies for touch tone 3
  {770,1209}, // frequencies for touch tone 4
  {770,1336}, // frequencies for touch tone 5
  {770,1477}, // frequencies for touch tone 6
  {852,1209}, // frequencies for touch tone 7
  {852,1336}, // frequencies for touch tone 8
  {852,1477}, // frequencies for touch tone 9
  {941,1209}, // frequencies for touch tone *
  {941,1477}, // frequencies for touch tone #
};

void setup() 
{
  mySid.begin();
  
  mySid.setADSR(0,1,1,255,1); 
  mySid.setWaveForm(0,TRIANGLE);

  mySid.setADSR(2,1,1,255,1); 
  mySid.setWaveForm(2,TRIANGLE);
}

void playDTMF(uint8_t digit, uint16_t duration_ms)
{
  mySid.setFrequency(0,DTMF[digit][0]);
  mySid.setFrequency(2,DTMF[digit][1]);
  mySid.noteOn(0);
  mySid.noteOn(2);
  delay(duration_ms);
  mySid.noteOff(0);
  mySid.noteOff(2);
  delay(50);
}

void dialNumber(char * number)
{
  uint16_t duration_ms=300;
  
  while(*number!=0)
  {
    if(*number=='*')playDTMF(10,duration_ms);
    if(*number=='#')playDTMF(11,duration_ms);
    int16_t n=*number-'0';
    if( (n<10) && (n>0) ) playDTMF(n,duration_ms);
    number++;
  }
}

void loop() 
{
  dialNumber("(0761) 201-569");
  //playDTMF(1,3000);
  delay(3000);
}


