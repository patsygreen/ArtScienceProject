#include <CD74HC4067.h>
#define pin1 0 
#define pin2 1 
#define pin3 2 
#define pin4 3 
#define pin5 21
const int g_common_output = pin5;


CD74HC4067 output_mux(pin1,pin2,pin3,pin4);
int incomingByte = 0; // for incoming serial data

void setup_mux() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT); 
  pinMode(pin5, OUTPUT);
  digitalWrite(g_common_output, LOW);
  delay(1000);
  Serial.println("ESP32-C3 MUX test");
}

void all_mux(){
   digitalWrite(g_common_output, HIGH);
    for (int i = 0; i < 16; i++) { //16 max
        output_mux.channel(i);
        delay(50);
    }
    delay(250);
   digitalWrite(g_common_output, LOW);
    for (int i = 0; i < 16; i++) {
        output_mux.channel(i);
        delay(50);
    }
    delay(250);
}

struct OutputAction {
  int channel;             // 0–15 or however many channels you use
  unsigned long duration;  // milliseconds
  const char* name;        // optional label
};

OutputAction sequence[] = { // Here you create a sequence
  {10, 250, "out15"},   
  {-1, 5000, "pause"},   
  {15, 150, "out15"},   
  {-1, 5000, "pause"},  
  {12, 250, "pause"},
  {-1, 5000, "pause"},   
};

const int sequenceLength = sizeof(sequence) / sizeof(sequence[0]);

int currentStep = 0;
bool stepActive = false;
unsigned long stepStartTime = 0;

void mux_sequence_runner() {
  unsigned long now = millis();

  if (!stepActive) {
    // Start next step
    OutputAction &action = sequence[currentStep];
    if (action.channel >= 0) {
      output_mux.channel(action.channel);
      digitalWrite(g_common_output, HIGH);
      Serial.printf("Starting %s (channel %d) for %lu ms\n", 
                    action.name, action.channel, action.duration);
    } else {
      // Pause
      digitalWrite(g_common_output, LOW);
      Serial.printf("Pausing for %lu ms\n", action.duration);
    }

    stepStartTime = now;
    stepActive = true;
  }

  if (stepActive && now - stepStartTime >= sequence[currentStep].duration) {
    // End this step
    digitalWrite(g_common_output, LOW);
    stepActive = false;
    currentStep++;

    if (currentStep >= sequenceLength) {
      // sequence done, reset or stop
      currentStep = 0; // repeat sequence
      Serial.println("Sequence complete, restarting...");
    }
  }
}


void mux_test(){

}