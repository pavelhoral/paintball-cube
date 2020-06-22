#ifndef MANUALINPUT_H
#define MANUALINPUT_H

#include <Arduino.h>

const uint8_t JACK_PINS[] = { A0, A1, A2 };
const uint8_t JACK_COUNT = 3;

const uint8_t METER_PIN = A5;

const uint8_t SWITCH_PIN = PIN2;

class ManualInput_ {
public:
  ManualInput_();

  /**
   * Read jack input state (each value is read as a corresponding bit flag).
   */
  uint8_t readJacks();

  /**
   * Read potentiometer value in the range [0-10].
   */
  uint8_t readMeter();

  /**
   * Read switch value.
   */
  boolean readSwitch(boolean raw = false);
};

#endif
