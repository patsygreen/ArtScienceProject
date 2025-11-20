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


#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
#include "mux2.h"
#include "adc.h"
#include "pwm.h"

DFRobot_VL53L0X sensor;

const uint8_t LED_Microscopy = 7;          // example: built-in LED on many boards
// const uint8_t LED_activateInteraction = 10; // example pin for interaction LED

// ...existing code...


void setup() {
  //initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //join i2c bus (address optional for master)
  // Wire.begin();
  // //Set I2C sub-device address
  // sensor.begin(0x50);
  // //Set to Back-to-back mode and high precision mode
  // sensor.setMode(sensor.eContinuous,sensor.eHigh);
  // //Laser rangefinder begins to work
  // sensor.start();

  pinMode(LED_Microscopy, OUTPUT);
  // pinMode(LED_activateInteraction, OUTPUT);
}

void loop() 
{

//turn the output channel to HIGH > to connect ground to LED's > test tmr
// digitalWrite(g_common_output, HIGH);
// output_mux.channel(10);
// digitalWrite(LED_Microscopy, HIGH); // Turn the Microscopy LED on

// // preprogrammed cycle for valves, uses the same timing as pwm
// // valves go on and off at the same time
// // change the timing in the pwm file

all_mux(); 

// //reduced speed preprogrammed cycle for algae, using pwm 
// // speed can be changed on both motors see pwm file 
// //both waterpumps go on and off at the same time
// //12 volt! 
pump_reduced_speed1();

//constant air circulation
//5 volt!
// digitalWrite(g_common_output, HIGH);
// output_mux.channel(8);

// code for distance button
// 5 volt!

// if(sensor.getDistance() <100){
//   Serial.println("cycle off");
//   analogWrite(PWM1_CHANNEL, 0); //255 max
//   analogWrite(PWM2_CHANNEL, 0); //255 max
//   highPhasePWM = false;
// }else{  
//   // Serial.println("No object within 100mm");
//   Serial.println("cycle on");
//   analogWrite(PWM1_CHANNEL, 128); //255 max
//   analogWrite(PWM2_CHANNEL, 128); //255 max
//   highPhasePWM = true;
//   delay(1000);
// }


}




