#include <Arduino.h>

#define PWM1_CHANNEL 20
#define PWM2_CHANNEL 10
#define PWM3_CHANNEL 7

void setup_pwm() {
    pinMode(PWM1_CHANNEL, OUTPUT);
    pinMode(PWM2_CHANNEL, OUTPUT);
    pinMode(PWM3_CHANNEL, OUTPUT);
}

void ramp(){
    for (int duty = 0; duty <= 255; duty++) { //255 max
        analogWrite(PWM1_CHANNEL, duty);
        analogWrite(PWM2_CHANNEL, duty);
        analogWrite(PWM3_CHANNEL, duty);
        delay(10);
    }
    
}