#ifndef NERVOUSMETER_H
#define NERVOUSMETER_H

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class nervousMeter
{
  private:
  uint8_t nervousMeterPin;

  public:
  inline nervousMeter(uint8_t&) __attribute__((always_inline));;
  inline void begin() __attribute__((always_inline));;
  inline bool touched() __attribute__((always_inline));;
};

nervousMeter::nervousMeter(uint8_t& nervousMeterPin)
{
  this->nervousMeterPin = nervousMeterPin;
}

void nervousMeter::begin()
{
  pinMode(nervousMeterPin, HIGH);
  digitalWrite(nervousMeterPin, LOW);
}

bool nervousMeter::touched()
{
  if(digitalRead(nervousMeterPin) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#endif NERVOUSMETER_H
