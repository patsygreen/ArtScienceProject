#include <CD74HC4067.h>
#define pin1 0 
#define pin2 1 
#define pin3 2 
#define pin4 3 
#define pin5 20

const int PWM_PIN = 6;      // your pwm1 pin
const int PWM_CHANNEL = 0;  // LEDC channel
const int PWM_FREQ = 1000;  // 1 kHz PWM good for small motors
const int PWM_RES = 10;     // 10-bit resolution (0–1023 duty)

CD74HC4067 output_mux(pin1,pin2,pin3,pin4);
const int g_common_output = pin5;
int incomingByte = 0; // for incoming serial data

void setup_mux() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT); 
  pinMode(pin5, OUTPUT);
  digitalWrite(g_common_output, LOW);
  delay(1000);
  //pinMode(PWM_PIN, OUTPUT);
  Serial.println("ESP32-C3 MUX test");
//   ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
//   ledcAttachPin(PWM_PIN, PWM_CHANNEL);

//   // start off
//   ledcWrite(PWM_CHANNEL, 0);
//   Serial.println("PWM setup done");
}

// Non-blocking state machine for mux sequence

const unsigned long HIGH_DURATION = 60000;  // ms per channel high
const unsigned long LOW_DURATION  = 30000;  // ms per channel low

int currentChannel = 0;
bool highPhase = true;              // HIGH phase or LOW phase
unsigned long lastStepTime = 0;

void all_mux_nonblocking() {
  unsigned long now = millis();

  if (highPhase) {
    if (now - lastStepTime >= HIGH_DURATION) {
      // advance to next channel
      currentChannel++;
      Serial.println("ON");
      if (currentChannel >= 8) {
        // switch to low phase
        highPhase = false;
        currentChannel = 0;
        digitalWrite(g_common_output, LOW);
      } else {
        output_mux.channel(currentChannel);
        lastStepTime = now;
      }
    }
  } else { // lowPhase
    if (now - lastStepTime >= LOW_DURATION) {
      currentChannel++;
      Serial.println("OFF");
      if (currentChannel >= 8) {
        // reset to high phase
        highPhase = true;
        currentChannel = 0;
        digitalWrite(g_common_output, HIGH);
        output_mux.channel(currentChannel);
      } else {
        output_mux.channel(currentChannel);
        lastStepTime = now;
      }
    }
  }
}

unsigned long rampHighDuration = 100;
bool rampIncreasing = true;
int rampCurrentChannel = 0;
bool rampHighPhase = true;
unsigned long rampLastStepTime = 0;

void all_mux_ramping() {
  unsigned long now = millis();

  if (rampHighPhase) {
    if (now - rampLastStepTime >= rampHighDuration) {
      rampCurrentChannel++;
      if (rampCurrentChannel >= 8) {
        rampHighPhase = false;
        rampCurrentChannel = 0;
        digitalWrite(g_common_output, LOW);

        // adjust rampHighDuration for next cycle
        if (rampIncreasing) {
          rampHighDuration += 100;
          if (rampHighDuration >= 150) {
            rampHighDuration = 150;
            rampIncreasing = false;
          }
        } else {
          rampHighDuration -= 100;
          if (rampHighDuration <= 100) {
            rampHighDuration = 100;
            rampIncreasing = true;
          }
        }
      } else {
        output_mux.channel(rampCurrentChannel);
        rampLastStepTime = now;
      }
    }
  } else {
    if (now - rampLastStepTime >= LOW_DURATION) {
      rampCurrentChannel++;
      if (rampCurrentChannel >= 8) {
        rampHighPhase = true;
        rampCurrentChannel = 0;
        digitalWrite(g_common_output, HIGH);
        output_mux.channel(rampCurrentChannel);
      } else {
        output_mux.channel(rampCurrentChannel);
        rampLastStepTime = now;
      }
    }
  }
}

// --- Begin global state for all_mux_odd_even ---
int oddEvenCurrentChannel = 0;
bool firingEvens = true;
int evenFireCount = 0;
unsigned long oddEvenLastStep = 0;
unsigned long pauseDuration = 100;
bool pausePhase = false;
unsigned long pulseStart = 0;
bool pulseActive = false;
unsigned long pulseDuration = 5; // ms
// --- End global state for all_mux_odd_even ---

void all_mux_odd_even() {
  unsigned long now = millis();

  if (pausePhase) {
    if (now - oddEvenLastStep >= pauseDuration) {
      pausePhase = false;
      firingEvens = !firingEvens;
      oddEvenCurrentChannel = firingEvens ? 0 : 1;
      evenFireCount = 0;
      oddEvenLastStep = now;
    }
    return;
  }

  if (!pulseActive && now - oddEvenLastStep >= HIGH_DURATION) {
    output_mux.channel(oddEvenCurrentChannel);
    digitalWrite(g_common_output, HIGH);
    pulseStart = now;
    pulseActive = true;
  }

  if (pulseActive && now - pulseStart >= pulseDuration) {
    digitalWrite(g_common_output, LOW);
    pulseActive = false;

    if (firingEvens) {
      evenFireCount++;
      if (evenFireCount >= 3) {
        oddEvenCurrentChannel += 2;
        evenFireCount = 0;
      }
    } else {
      oddEvenCurrentChannel += 2;
    }

    oddEvenLastStep = now;

    if (oddEvenCurrentChannel >= 8) {
      pausePhase = true;
      pauseDuration = random(200, 800);
    }
  }
}

void all_mux(){
   digitalWrite(g_common_output, HIGH);
    for (int i = 0; i < 16; i++) { //16 max
        output_mux.channel(i);
        delay(500);
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

// OutputAction sequence[] = {
//   {6, 500, "out7"},   // 1s of out7
//   {-1, 2000, "pause"},  // special pause (no output)
//   {0, 1000, "out1"},   // 2s of out1
//   {-1, 1000, "pause"}  // special pause (no output)
//   {0, 1000, "out1"},   // 2s of out1
//   {-1, 1000, "pause"},  // special pause (no output)
//   {0, 2000, "out1"},   // 2s of out1
//   {-1, 1000, "pause"}  // special pause (no output)
// };


// Example sequence (can be updated anytime)
OutputAction sequence[] = {
  {6, 500, "out7"},   // 1s of out7
  {-1, 1000, "pause"},   // 5s of out5
  {0, 5000, "out1"},   // 2s of out1
  {-1, 5000, "pause"}  // special pause (no output)
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
