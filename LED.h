#pragma once

class led
{
  private:
  int8_t ledPin;
  
  public:
  //Function prototypes
  inline led(int8_t) __attribute__((always_inline));
  inline ~led() __attribute__((always_inline));
  inline void begin() __attribute__((always_inline));
  inline void on() __attribute__((always_inline));
  inline void off() __attribute__((always_inline));
  inline void toggle() __attribute__((always_inline));
};

//parametrized constructor
led::led(int8_t ledPin) {
  this->ledPin = ledPin;
}

void led::begin() {
  pinMode(ledPin, OUTPUT);
}

void led::on()
{
  digitalWrite(ledPin, HIGH); 
}

void led::off()
{
  digitalWrite(ledPin, LOW);
}

void led::toggle()
{
  static unsigned long ledMillis = millis();
  if(millis() - ledMillis > 500)
  {
    digitalWrite(ledPin, !digitalRead(ledPin));
    ledMillis = millis();  
  }
}

//Destructor
led::~led()
{
  Serial.println("led object destroyed");
}
