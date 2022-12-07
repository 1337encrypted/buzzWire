#ifndef BUZZWIRE_H
#define BUZZWIRE_H

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

class buzzWire
{
  private:
  uint8_t buzzWirePin;

  public:
  inline buzzWire(uint8_t&) __attribute__((always_inline));;
  inline void begin() __attribute__((always_inline));;
  inline bool touched() __attribute__((always_inline));;
};

buzzWire::buzzWire(uint8_t& buzzWirePin)
{
  this->buzzWirePin = buzzWirePin;
}

void buzzWire::begin()
{
  pinMode(buzzWirePin, HIGH);
  digitalWrite(buzzWirePin, LOW);
}

bool buzzWire::touched()
{
  if(digitalRead(buzzWirePin) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#endif BUZZWIRE_H
