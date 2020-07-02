#include "FrontLight.hpp"

FrontLight::FrontLight() {
  pinMode(LIGHT_RED_PIN, OUTPUT);
  pinMode(LIGHT_GREEN_PIN, OUTPUT);
  pinMode(LIGHT_BLUE_PIN, OUTPUT);
  reset();
}

void FrontLight::reset() {
    setLevels(0, 0, 0);
}

void FrontLight::setLevels(uint8_t r, uint8_t g, uint8_t b) {
  analogWrite(LIGHT_RED_PIN, 255 - r);
  analogWrite(LIGHT_GREEN_PIN, 255 - g);
  analogWrite(LIGHT_BLUE_PIN, 255 - b);
}
