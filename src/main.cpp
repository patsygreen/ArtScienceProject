
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


#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
#include "mux.h"
#include "adc.h"

DFRobot_VL53L0X sensor;


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
}

void loop() 
{

all_mux_nonblocking(); 

if(sensor.getDistance() <100){
  Serial.println("cycle off");
   digitalWrite(g_common_output, LOW);
  //  highPhase = false;
}else{  
  // Serial.println("No object within 100mm");
   digitalWrite(g_common_output, HIGH);
  //  highPhase = true;
}
  // //Get the distance
  // Serial.print("Distance: ");Serial.println(sensor.getDistance());
  // //The delay is added to demonstrate the effect, and if you do not add the delay,
  // //it will not affect the measurement accuracy
  // delay(500);
}

// #include "Adafruit_VL53L1X.h"
// #include <Arduino.h>
// #include "mux.h"
// #include "adc.h"


// #define IRQ_PIN 2
// #define XSHUT_PIN 3

// Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) delay(10);

//   Serial.println(F("Adafruit VL53L1X sensor demo"));

//   Wire.begin();
//   if (! vl53.begin(0x29, &Wire)) {
//     Serial.print(F("Error on init of VL sensor: "));
//     Serial.println(vl53.vl_status);
//     while (1)       delay(10);
//   }
//   Serial.println(F("VL53L1X sensor OK!"));

//   Serial.print(F("Sensor ID: 0x"));
//   Serial.println(vl53.sensorID(), HEX);

//   if (! vl53.startRanging()) {
//     Serial.print(F("Couldn't start ranging: "));
//     Serial.println(vl53.vl_status);
//     while (1)       delay(10);
//   }
//   Serial.println(F("Ranging started"));

//   // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
//   vl53.setTimingBudget(50);
//   Serial.print(F("Timing budget (ms): "));
//   Serial.println(vl53.getTimingBudget());

//   /*
//   vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
//   vl.VL53L1X_SetInterruptPolarity(0);
//   */
// }

// void loop() {
//   int16_t distance;

//   if (vl53.dataReady()) {
//     // new measurement for the taking!
//     distance = vl53.distance();
//     if (distance == -1) {
//       // something went wrong!
//       Serial.print(F("Couldn't get distance: "));
//       Serial.println(vl53.vl_status);
//       return;
//     }
//     Serial.print(F("Distance: "));
//     Serial.print(distance);
//     Serial.println(" mm");

//     // data is read out, time for another reading!
//     vl53.clearInterrupt();
//   }
// }

 // --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
// 
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//
// #include <Arduino.h>
// #include <Wire.h>


// void setup()
// {
//   Wire.begin();

//   Serial.begin(9600);
//   while (!Serial);             // Leonardo: wait for serial monitor
//   Serial.println("\nI2C Scanner");
// }


// void loop()
// {
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for(address = 1; address < 127; address++ ) 
//   {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16) 
//         Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println("  !");

//       nDevices++;
//     }
//     else if (error==4) 
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address<16) 
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }    
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");

//   delay(5000);           // wait 5 seconds for next scan
// }