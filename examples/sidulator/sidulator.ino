/*
   Sidulator Synth Stereo

   This is a creative synthesizer where you can controll the the oscillators
   creating stereo sounds with the 3 potientiomets

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

// pin defintions

//****************** AUDIO PIN DEFINITIONS ********************
#define AUDIO_OUTPUT_PWM_LEFT   9
#define AUDIO_OUTPUT_PWM_RIGHT  10

//********** POTENTIOMETER PIN DEFINITIONS ********************
#define POTI1 A2
#define POTI2 A3
#define POTI3 A4

//******************** LED PIN DEFINITIONS ********************
#define NUMBER_OF_LEDS 11 // including the 7 segment display

#define LED_ARDUINO 13
#define LED_LEFT    A0
#define LED_RIGHT   A1

//************ 7 SEGMENT DISPLAY PIN DEFINITIONS **************
// seven segment display has a common anode
/*
 *    A
 *    -- 
 * F |  | B 
 *    -- G
 * E |  | C
 *    -- . DP
 *    D
 */
#define NUMBER_OF_SEGMENTS 8

#define SEG_A  2
#define SEG_B 11
#define SEG_C  6
#define SEG_D  4
#define SEG_E  7
#define SEG_F  8
#define SEG_G  3
#define SEG_DP 5

//****************** BUTTON PIN DEFINITIONS *******************
#define NUMBER_OF_BUTTONS 3
#define BUTTON_COMMON_INPUT 12
// drive columns low to select key
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

const uint8_t Segments[]   = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP, LED_LEFT, LED_RIGHT, LED_ARDUINO};
const uint8_t LedPolarity[] = {0, 0, 0, 0, 0, 0, 0, 0 , 1       , 1        , 1};
uint8_t LedState[NUMBER_OF_LEDS];
const uint8_t Buttons[] = {BUTTON1, BUTTON2, BUTTON3};

void setLed(uint8_t n, uint8_t onOff)
{
  LedState[n] = onOff;
  if (onOff == 1)
  {
    if (LedPolarity[n] == 1) digitalWrite(Segments[n], HIGH);
    else digitalWrite(Segments[n], LOW);
  } else
  {
    if (LedPolarity[n] == 1) digitalWrite(Segments[n], LOW);
    else digitalWrite(Segments[n], HIGH);
  }
}

void ledRestore()
{
  for ( int n = 0; n < NUMBER_OF_LEDS; n++)
  {
    pinMode(Segments[n], OUTPUT);
    setLed(n, LedState[n]);
  }
}

uint8_t getButton()
{
  digitalWrite(BUTTON1, HIGH);
  digitalWrite(BUTTON2, HIGH);
  digitalWrite(BUTTON3, HIGH);
  
  uint8_t value = 0;
  
  digitalWrite(BUTTON1, LOW);
  if (digitalRead(BUTTON_COMMON_INPUT))value = 1;
  digitalWrite(BUTTON2, LOW);
  if (digitalRead(BUTTON_COMMON_INPUT))value = 2;
  digitalWrite(BUTTON3, LOW);
  if (digitalRead(BUTTON_COMMON_INPUT))value = 3;

  ledRestore();
  
  return value;
}

boolean isButtonPressed()
{
  if ( getButton() !=  0) return true;
  else return false;
}

void toggleLed(uint8_t ledNumber)
{
  LedState[ledNumber] = LedState[ledNumber] ^ 0x01;
  setLed(ledNumber, LedState[ledNumber] );
}

void lauflicht(uint16_t time_ms)
{
  for (int n = 0; n < NUMBER_OF_LEDS; n++)
  {
    setLed(n, 1);
    delay(time_ms);
    setLed(n, 0);
  }
}

void circleDisplayNext()
{
  static uint8_t pos = 0, pos1 = 4;
  //toggleLed(pos);
  pos++;
  if (pos > 5)pos = 0;
  pos1++;
  if (pos1 > 5)pos1 = 0;
  setLed(pos, 1);
  setLed(pos1, 0);
}


void setup()
{
  for ( int n = 0; n < NUMBER_OF_BUTTONS; n++)
  {
    pinMode(Segments[n], OUTPUT);
    digitalWrite(Segments[n], HIGH);
  }
  pinMode(BUTTON_COMMON_INPUT, INPUT_PULLUP);
  digitalWrite(BUTTON_COMMON_INPUT, HIGH);

  for ( int n = 0; n < NUMBER_OF_LEDS; n++)
  {
    pinMode(Segments[n], OUTPUT);
    setLed(n, 1);
  }

  delay(100);

  mySid.begin();
  mySid.setWaveForm(0, TRIANGLE);
  mySid.setWaveForm(1, TRIANGLE);
}

void loop()
{
  lauflicht(100);
  for (int n = 0; n < 20; n++)
  {
    circleDisplayNext();
    delay(25);
  }

  while (1)
  {

    uint8_t b;
    static uint8_t channel = 0;
    b = getButton();
    //setLed(b, 1);

    circleDisplayNext();
    
    if (b == 0)
    {
      mySid.setAmplitude(channel, 0);
      //mySid.noteOff(channel);
    } else
    {
      mySid.setFrequency(channel, analogRead(POTI1));
      delay(20);

      mySid.setAmplitude(channel, analogRead(POTI2) / 2);
      delay(20);
    }
    if (b == 1)
    {
      channel = 0;
    }
    if (b == 2)
    {
      channel = 1;

    }
    //setLed(b, 0);
  }

}
