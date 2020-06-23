#include <Arduino.h>

#include "modules/Peripherals.hpp"
#include "interface/GameFace.hpp"

Peripherals module;

void setup() {
  Serial.begin(9600);
  GameFace.setup();  
  module.setup();
}

void loop() {
  module.loop();
}
