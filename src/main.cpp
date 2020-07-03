#include <Arduino.h>
#include <SPI.h>

#include "context.hpp"

Context context;

#include "modules/SystemTest.hpp"

SystemTest module(context);

void setup() {
  SPI.begin();
  Serial.begin(9600);
  context.audio.setup();
  context.rfid.setup();
  module.setup();
}

void loop() {
  module.loop();
}
