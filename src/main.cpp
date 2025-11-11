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

//possible debug for LED's > turn the output channel to HIGH 
//to connect ground to LED's > test tmr
digitalWrite(g_common_output, HIGH);
output_mux.channel(9);

digitalWrite(LED_Microscopy, HIGH); // Turn the Microscopy LED on


// // preprogrammed cycle for algae using mux, full speed 
// //both waterpumps and valves go on and off at the same time
// //uncomment to use function
// all_mux_nonblocking(); 

// // preprogrammed cycle for valves, uses the same timing as pwm
// // valves go on and off at the same time
// // change the timing in the pwm file
all_mux(); 

// //reduced speed preprogrammed cycle for algae, using pwm 
// // speed can be changed on both motors see pwm file 
// //both waterpumps go on and off at the same time
// //12 volt! 
pump_reduced_speed1();

// code for distance button
// 5 volt!
if(sensor.getDistance() <100){
  Serial.println("cycle off");
  analogWrite(PWM1_CHANNEL, 0); //255 max
  analogWrite(PWM2_CHANNEL, 0); //255 max
  highPhasePWM = false;
digitalWrite(LED_activateInteraction, HIGH); // Turn the Interaction LED on
}else{  
  // Serial.println("No object within 100mm");
  analogWrite(PWM1_CHANNEL, 128); //255 max
  analogWrite(PWM2_CHANNEL, 100); //255 max
   highPhasePWM = true;
  if(LED_activateInteraction == HIGH){ // blink led if no person close by?
  delay(1000);
  digitalWrite(LED_activateInteraction, LOW); // Turn the Interaction LED off
} else{
  delay(1000);
  digitalWrite(LED_activateInteraction, HIGH); // Turn the Interaction LED on
}
}

//constant air circulation
//5 volt!
digitalWrite(g_common_output, HIGH);
output_mux.channel(8);

}

