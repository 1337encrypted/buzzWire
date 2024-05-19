#include "GLOBALS.h"

void setup() 
{
  bleSerial.Begin(9600);

  pinMode(buzzWirePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buzzWirePin), touched, FALLING);

  bleSerial.println("\nPress S to start\nX to STOP\nand R to reset");
}

void touched() {

  uint32_t currentTime = millis()

  if ((currentTime - lastDebounceTime) > 20) {
    lastDebounceTime = currentTime;
    status = TOUCH;
  }
}


void loop() {

  if(bleSerial.available() > 0){
    status = (states)bleSerial.read();
  }

  switch(status)
  {
    case START:
    break;

    case PAUSE:

    case RELEASED:
    buzz.off();

    if(!display.counter)
      status = GAMEOVER;
    break; 

    case TOUCHED:
    buzz.on();

    if(lives)
      leds[lives--].on();
    else
      status = GAMEOVER;
    break;
    
    case GAMEOVER:
    buzz.alarm();
    break;

    case RESET:
    lives = 0;

    for (int i = 0; i < lives; ++i) {
      leds[i].off();
    }
    break;
  }
}
