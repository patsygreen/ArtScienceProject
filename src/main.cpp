#include <Arduino.h>
#include "mux.h"
#include "adc.h"

void setup() {
  Serial.begin(115200);

}

void loop() {

  all_mux_nonblocking();

}
