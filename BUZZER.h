#pragma once
  
class buzzer
{
  public: 
  uint8_t buzzpin;
    
  //Function prototype
  buzzer(int8_t) __attribute__((always_inline));
  void begin() __attribute__((always_inline));
  inline void on(uint16_t) __attribute__((always_inline));
  inline void off() __attribute__((always_inline));
  inline void alarm() __attribute__((always_inline));
  inline ~buzzer() __attribute__((always_inline));
};

//Parametrized constructor
buzzer::buzzer(int8_t buzzpin)
{
  this->buzzpin = buzzpin;
}

void buzzer::begin()
{
  pinMode(buzzpin, OUTPUT);
}

void buzzer::alarm()
{
  on(660);
  delay(150);
  on(660);
  delay(300);
  off();
}

void buzzer::on(uint16_t note)
{
  static unsigned long buzzMillis = millis();                   //Assigns the current snapshot of time only the first
  if(millis() - buzzMillis > 10)
  {
    tone(buzzpin, note, 100);
    buzzMillis = millis();  
  }
}

void buzzer::off()
{
  noTone(buzzpin);
}

//Destructor
buzzer::~buzzer()
{
  Serial.println("buzzer object destroyed"); 
}
