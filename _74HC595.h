#ifndef _74HC595_H
#define _74HC595_H

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class _74HC595
{
  private:
  uint8_t latchPin;      // ST_CP [RCK] on 74HC595
  uint8_t clockPin;      // SH_CP [SCK] on 74HC595
  uint8_t dataPin;       // DS [S1] on 74HC595
  
  byte seg_digits[10] = 
  { 
    B10000001,  // = 0
    B11001111,  // = 1
    B10010010,  // = 2
    B10000110,  // = 3
    B11001100,  // = 4
    B10100100,  // = 5
    B10100000,  // = 6
    B10001111,  // = 7
    B10000000,  // = 8
    B10000100   // = 9
  };

  public:
  inline _74HC595(uint8_t&,uint8_t&,uint8_t&) __attribute__((always_inline));;
  inline void begin() __attribute__((always_inline));;
  inline void displayDigit(int) __attribute__((always_inline));;
};

_74HC595::_74HC595(uint8_t& latchPin, uint8_t& clockPin, uint8_t& dataPin)
{
  this->latchPin = latchPin;
  this->clockPin = clockPin;
  this->dataPin = dataPin;
}

void _74HC595::begin()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  displayDigit(0);
}

void _74HC595::displayDigit(int x)
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, seg_digits[x]);
   digitalWrite(latchPin, HIGH);
}

#endif _74HC595_H
