#include <Arduino.h>
#include "mux.h"
#include "adc.h"


#define LED_PIN 8
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //// preprogrammed cycle for algae 
  ////both waterpump and valve go on and off at the same time
  // all_mux_nonblocking(); 


int touch= analogRead(A0);


  //simple code for waterlevel sensor
  //uses a optical sensor for reflection of the water


// int x= analogRead(A0);
// Serial.printf("Analog Read: %d\n", x); //using printf, prints it into terminnal
// delay(250);

// if(x <1000){ //no water
// digitalWrite(LED_PIN, LOW);
// }else{ //reaches water
// digitalWrite(LED_PIN, HIGH);
// }


}
