#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include "context.hpp"

Context context;

SoftwareSerial serial(10, 11);

#include "modules/SystemTest.hpp"

SystemTest module(context);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  context.audio.setup(Serial);
  context.rfid.setup();
  module.setup();
  context.audio.play(1, 1);
}

void loop() {
  module.loop();
}
