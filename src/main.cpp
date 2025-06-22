#include "HomeSpan.h" 
#include "DEV_LED.h"  

DEV_DimmableLED *myLED; // calling function from DEV_LED.h

int CAPACITIVE_THRESHOLD = 3; // emperical treshold for capacitive button. You can replace it for physical button check.
#define capacitive_pin = T9; 

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

  Serial.println(touchRead(capacitive_pin)); // reading capacitive sensor from pin 32

  if (touchRead(capacitive_pin) < CAPACITIVE_THRESHOLD) 
  {
    myLED->touch(); // Calling function form DEV_LED.h
    delay(100);
  }
}
