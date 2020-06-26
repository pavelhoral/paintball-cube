#include <Arduino.h>
#include <SPI.h>

#include "context.hpp"

Context context;

#include "modules/Peripherals.hpp"

Peripherals module(context);

void setup() {
  SPI.begin();
  Serial.begin(9600);
  context.rfid.setup();
  module.setup();
}

void loop() {
  module.loop();
}
