#include <Arduino.h>


#define PWM1_CHANNEL 20
#define PWM2_CHANNEL 10
#define PWM3_CHANNEL 7

void setup_pwm() {
    pinMode(PWM1_CHANNEL, OUTPUT);
    pinMode(PWM2_CHANNEL, OUTPUT);
    pinMode(PWM3_CHANNEL, OUTPUT);
}

const unsigned long ON_DURATION = 1000;  // ms per channel high
const unsigned long OFF_DURATION  = 500;  // ms per channel low
bool highPhasePWM = true;              // HIGH phase or LOW phase
unsigned long lastStepTimePWM = 0;

//reduced speed function with timing intervals 
//0 is off, 255 is full speed
void pump_reduced_speed1(){
    unsigned long nowPWM = millis();
if (highPhasePWM) {
    if (nowPWM - lastStepTimePWM >= ON_DURATION) {
      Serial.printf("ON waterpump 0");
        // switch to low phase
        highPhasePWM = false;
        analogWrite(PWM1_CHANNEL, 0); //255 max
        analogWrite(PWM2_CHANNEL, 0); //255 max
        lastStepTimePWM = nowPWM;
      }
    } else { // lowPhase
    if (nowPWM - lastStepTimePWM >= OFF_DURATION) {
      Serial.printf("OFF waterpump 0"); 
        // reset to high phase
        highPhasePWM = true;
        analogWrite(PWM1_CHANNEL, 128); //speed
        analogWrite(PWM2_CHANNEL, 100); //speed
        lastStepTimePWM = nowPWM;
      }
    }
}

void ramp(){
    for (int duty = 0; duty <= 255; duty++) { //255 max
        analogWrite(PWM1_CHANNEL, duty);
        analogWrite(PWM2_CHANNEL, duty);
        analogWrite(PWM3_CHANNEL, duty);
        delay(10);
    }
    
}