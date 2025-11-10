
// //   //// preprogrammed cycle for algae 
// //   ////both waterpump and valve go on and off at the same time
// //   // all_mux_nonblocking(); 


// //   //simple code for waterlevel sensor
// //   //uses a optical sensor for reflection of the water


// // // int x= analogRead(A0);
// // // Serial.printf("Analog Read: %d\n", x); //using printf, prints it into terminnal
// // // delay(250);

// // // if(x <1000){ //no water
// // // digitalWrite(LED_PIN, LOW);
// // // }else{ //reaches water
// // // digitalWrite(LED_PIN, HIGH);
// // // }
//hello

#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
#include "mux.h"
#include "adc.h"

DFRobot_VL53L0X sensor;

const uint8_t LED_Microscopy = 7;          // example: built-in LED on many boards
const uint8_t LED_activateInteraction = 10; // example pin for interaction LED

// ...existing code...


void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //join i2c bus (address optional for master)
  Wire.begin();
  //Set I2C sub-device address
  sensor.begin(0x50);
  //Set to Back-to-back mode and high precision mode
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  //Laser rangefinder begins to work
  sensor.start();

  pinMode(LED_Microscopy, OUTPUT);
  pinMode(LED_activateInteraction, OUTPUT);
}

void loop() 
{

digitalWrite(LED_Microscopy, HIGH); // Turn the Microscopy LED on
digitalWrite(LED_activateInteraction, HIGH); // Turn the Interaction LED on

all_mux_nonblocking(); 

if(sensor.getDistance() <100){
  Serial.println("cycle off");
   digitalWrite(g_common_output, LOW);
   highPhase = false;
}else{  
  // Serial.println("No object within 100mm");
   digitalWrite(g_common_output, HIGH);
   highPhase = true;
}

//constant air circulation
//uncomment to start working
// digitalWrite(g_common_output, HIGH);
// output_mux.channel(8);

}

