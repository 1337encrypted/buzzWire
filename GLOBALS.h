#include "_74HC595.h"
#include "buzzWire.h"
#include "BUZZER.h"
#include "LED.h"

#define DEBUG 0

#if DEBUG == 1
  #define SerialBegin(x) Serial.begin(x)
  #define debug(x) Serial.print(x)
  #define debugln(x) Serial.println(x)
#else
  #define SerialBegin(x)
  #define debug(x)
  #define debugln(x) 
#endif

inline void gameover() __attribute__((always_inline));


//SEVEN SEGMENT DISPLAY
uint8_t latchPin = 3;
uint8_t clockPin = 2;
uint8_t dataPin = 4;
_74HC595 display(latchPin, clockPin, dataPin);

//BUZZER
uint8_t buzzPin = 9;
buzzer buzz(buzzPin);

//GO LED
uint8_t goLedPin = 7;
led goLed(goLedPin);

//STOP LED
uint8_t stopLedPin = 6;
led stopLed(stopLedPin);

//TOUCH STRING
uint8_t touchPin = 10;
buzzWire wire(touchPin);

//STATES
enum class states : uint8_t
{
  GO,
  TOUCHED,
  STOP,
  RESET
};
states status = states::GO;

const int fail_threshold = 9;
int failCounter = 0;

byte seg_spin[8] = 
{
  B10111111,
  B11011101,
  B11101011,
  B11110111,
  B10111111,
  B11011101,
  B11101011,
  B11110111
};

void gameover()
{
  for(int i = 7; i < sizeof(delays)/sizeof(delays[0]); i++)
  {
    tone(buzzPin, Tone1[i], Tone2[i]);
    display.displayDigit(seg_spin[i]);
    delay(delays[i]); 
  }
  noTone(buzzPin);
}
