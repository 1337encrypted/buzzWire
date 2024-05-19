#pragma once

class _74HC595
{
  private:
  int8_t dataPin;       // DS [S1] on 74HC595
  int8_t clockPin;      // SH_CP [SCK] on 74HC595
  int8_t latchPin;      // ST_CP [RCK] on 74HC595
  
  uint8_t digits[10] = {
    0b00111111, //0
    0b00000110, //1 
    0b01011011, //2
    0b01001111, //3 
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00000111, //7
    0b01111111, //8
    0b01101111  //9
  };

  public:
  inline _74HC595(int8_t&, int8_t&, int8_t&) __attribute__((always_inline));
  inline void begin() __attribute__((always_inline));
  inline void shiftOut(uint8_t) __attribute__((always_inline));
  inline void displayDigit(uint) __attribute__((always_inline));
  inline void counter() __attribute__((always_inline));
};

_74HC595::_74HC595(int8_t& dataPin, int8_t& clockPin, int8_t& latchPin)
{
  this->dataPin = dataPin;
  this->clockPin = clockPin;
  this->latchPin = latchPin;
}

void _74HC595::begin()
{
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  displayDigit(00);
}

void _74HC595::shiftOut(uint8_t value) {
  for (uint8_t i = 0; i < 8; ++i) {
    // Extract the bit to send based on the bit order
    bool bitToSend = (value >> (7 - i)) & 0x01;

    // Send the bit out
    digitalWrite(dataPin, bitToSend);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
}

void _74HC595::displayDigit(uint8_t number)
{
  shiftOut(digits[number%10]);
  shiftOut(digits[number/10]);
  
  digitalWrite(latchPin, HIGH); 
  digitalWrite(latchPin, LOW);
}

bool _74HC595::counter() {
  static int8_t number = 0;
  static unsigned long prevousTime = millis();
  if(millis() - prevousTime > 1000)
  {
    displayDigit(number++);
    prevousTime = millis(); 

    if(number == 100)
      return false; 
  }
  return true;
}
