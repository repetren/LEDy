
#include "HomeSpan.h" 
#include "DEV_LED.h"  

DEV_DimmableLED *myLED; // This thing alowing to call functions from DEV_LED.h

void setup() {
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"Floorlamp");

  new SpanAccessory(); //initialising new acessory
  
    new Service::AccessoryInformation();
      new Characteristic::Identify();                       
  
    myLED = new DEV_DimmableLED(19); // Here added "myLED" to original sketch
}


void loop() {
  homeSpan.poll();

  Serial.println(touchRead(T9)); // reading capacitive sensor from pin 32

  if (touchRead(T9) < 3) // emperical treshold for capacitive button
  {
    myLED->touch(); // Calling function form DEV_LED.h
    delay(100);
  }
}
