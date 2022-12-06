/*Cannot create a .cpp file as inline prototypes need the function to be present in the same file as they are defined*/
#ifndef buzzer_h
#define buzzer_h

#if (ARDUINO >= 100) 
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

  int delays[] = {150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500};
  int Tone1[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480};
  int Tone2[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80};

  
class buzzer
{
  public: 
  uint8_t buzzpin;
    
  //Function prototype
//  inline buzzer() __attribute__((always_inline));
  inline void begin() __attribute__((always_inline));
  inline buzzer(uint8_t) __attribute__((always_inline));
  inline ~buzzer() __attribute__((always_inline));
  inline void initBuzzer() __attribute__((always_inline));
  inline void deinitBuzzer() __attribute__((always_inline));
  inline void alarm() __attribute__((always_inline));
  inline void on() __attribute__((always_inline));
  inline void off() __attribute__((always_inline));
};


////Default constructor
//buzzer::buzzer()
//{
//  //Initilize the buzzer
//  this->buzzpin = A5;
//}

//Parametrized constructor
buzzer::buzzer(const uint8_t buzzpin)
{
  //Initilize the buzzer
  this->buzzpin = buzzpin;
}

//Destructor
buzzer::~buzzer()
{
  Serial.println("buzzer object destroyed"); 
}

void buzzer::begin()
{
  //buzzer pin as output
  pinMode(buzzpin, OUTPUT);
}

void buzzer::initBuzzer()
{
  for(int i = 0; i < 7; i++)
  {
    tone(buzzpin, Tone1[i], Tone2[i]);
    delay(delays[i]); 
  }
  noTone(buzzpin);
}

void buzzer::deinitBuzzer()
{
  for(int i = 7; i < sizeof(delays)/sizeof(delays[0]); i++)
  {
    tone(buzzpin, Tone1[i], Tone2[i]);
    delay(delays[i]); 
  }
  noTone(buzzpin);
}

void buzzer::alarm()
{
  tone(buzzpin, 660, 100);
  delay(150);
  tone(buzzpin, 660, 100);
  delay(300);
  noTone(buzzpin);
}

void buzzer::off()
{
  noTone(buzzpin);
}

void buzzer::on()
{
  static unsigned long buzzMillis = millis();                   //Assigns the current snapshot of time only the first
                                                                //time this code executes
  if(millis() - buzzMillis > 10)
  {
    tone(buzzpin, 1000, 100);
    buzzMillis = millis();  
  }
}

#endif  //END BUZZER_H
