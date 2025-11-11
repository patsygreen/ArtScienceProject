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
int currentChannelPWM = 0;

//reduced speed function with timing intervals 
void pump_reduced_speed(){
    unsigned long nowPWM = millis();
if (highPhasePWM) {
    if (nowPWM - lastStepTimePWM >= ON_DURATION) {
      // advance to next channel
      currentChannelPWM++;
      Serial.printf("ON");
      if (currentChannelPWM >= 4) { 
        // switch to low phase
        highPhasePWM = false;
        currentChannelPWM = 0;
        analogWrite(PWM1_CHANNEL, 0); //255 max
        analogWrite(PWM2_CHANNEL, 0); //255 max
        output_mux.channel(currentChannelPWM);
      } else {
        output_mux.channel(currentChannelPWM);
        lastStepTimePWM = nowPWM;
      }
    }
  } else { // lowPhase
    if (nowPWM - lastStepTimePWM >= OFF_DURATION) {
      currentChannelPWM++;
      Serial.printf("OFF");
      if (currentChannelPWM >= 4) { 
        // reset to high phase
        highPhasePWM = true;
        currentChannelPWM = 0;
        analogWrite(PWM1_CHANNEL, 128); //255 max
        analogWrite(PWM2_CHANNEL, 128); //255 max
        output_mux.channel(currentChannelPWM);
      } else {
        output_mux.channel(currentChannelPWM);
        lastStepTimePWM = nowPWM;
      }
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