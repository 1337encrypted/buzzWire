#include "GLOBALS.h"

void setup() 
{
  // put your setup code here, to run once:
  SerialBegin(9600);       //Serial.begin(9600);
  display.begin();
  goLed.begin();
  stopLed.begin();
  buzz.begin();
  wire.begin();

  buzz.initBuzzer();
  goLed.off();
  stopLed.off();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(status)
  {
    case states::GO:
    debugln("GO state");
    goLed.on();
    stopLed.off();
    //You can put a interrupt here and leave the infinite loop on
    while(true)
    {
      debugln("GO loop");
      if(wire.touched())
      {
//        status = states::TOUCHED;
        break; 
      }
    }

    case states::TOUCHED:
    debugln("TOUCHED state");
    display.displayDigit(++failCounter);
    buzz.alarm();
    goLed.off();
    status = states::GO;
    
    if(failCounter > fail_threshold)
    {
      status = states::STOP;
    }    
    break;
    
    case states::STOP:
    debugln("STOP state");
    goLed.off();
    stopLed.on();
    while(true)
    {
      gameover();
      goLed.toggle();
      stopLed.toggle();
      delay(2000);
//      status = states::RESET;
      break;
    }

    case states::RESET:
    debugln("RESET state");
    goLed.off();
    stopLed.off();
    status = states::GO;
    failCounter = 0;
    display.displayDigit(0);
    buzz.initBuzzer();
    break;
  }
}
