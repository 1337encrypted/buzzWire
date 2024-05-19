#include<SoftwareSerial.h>
#include "_74HC595.h"
#include "buzzWire.h"
#include "BUZZER.h"
#include "LED.h"

constexpr int8_t RX = 11;
constexpr int8_t TX = 10;
//Bluetooth Serial setup
SoftwareSerial bleSerial(RX, TX);

//SEVEN SEGMENT DISPLAY
constexpr int8_t dataPin = 4;
constexpr int8_t latchPin = 3;
constexpr int8_t clockPin = 2;
_74HC595 display(dataPin, clockPin, latchPin);

//BUZZER
constexpr int8_t buzzPin = 9;
buzzer buzz(buzzPin);

int8_t lives = 4;
constexpr int8_t ledPin[lives] = {A5, A4, A3, A2};

for (int i = 0; i < lives; ++i) {
  led leds[ledPin[i]];
}

//TOUCH STRING
constexpr int8_t touchPin = 2;
uint32_t lastDebounceTime, debounceDelay;
buzzWire wire(touchPin);

//BUZZWIRE STATES
enum states : constexpr int8_t
{
  START = 'S'
  PAUSE = 'P',
  TOUCH 'T',
  LEAVE = 'L',
  WIN = 'W'
  LOSE = 'L'
  GAMEOVER = 'X'
  RESET = 'R'
};
volatile states status = STOP;

