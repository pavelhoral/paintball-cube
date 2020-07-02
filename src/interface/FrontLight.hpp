#ifndef FRONTLIGHT_H
#define FRONTLIGHT_H

#include <Arduino.h>

const uint8_t LIGHT_RED_PIN = 6;

const uint8_t LIGHT_GREEN_PIN = 5;

const uint8_t LIGHT_BLUE_PIN = 9;

class FrontLight {
public:
  FrontLight();

  /**
   * Reset any internal and physical state.
   */
  void reset();

  /**
   * Set light levels to the given values.
   */
  void setLevels(uint8_t r, uint8_t g, uint8_t b);

};

#endif
