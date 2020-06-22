#include <Arduino.h>
#include <SPI.h>

#include "modules/Peripherals.hpp"

Peripherals module;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  module.setup();
}

void loop() {
  module.loop();
}
