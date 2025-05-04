
#include "HomeSpan.h" 
#include "DEV_LED.h"  

void setup() {
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"Floorlamp");

  new SpanAccessory(); 
  
    new Service::AccessoryInformation();    
      new Characteristic::Identify();                       
  
    new DEV_DimmableLED(19); 
}


void loop() {
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}