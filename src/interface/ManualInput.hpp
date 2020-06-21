#ifndef MANUALINPUT_H
#define MANUALINPUT_H

#include <Arduino.h>

const uint8_t JACK_PINS[] = { A0, A1, A2 };
const uint8_t JACK_COUNT = 3;

const uint8_t METER_PIN = A5;

class ManualInput_ {
public:
  ManualInput_() {
    pinMode(JACK_PINS[0], INPUT_PULLUP);
    pinMode(JACK_PINS[1], INPUT_PULLUP);
    pinMode(JACK_PINS[2], INPUT_PULLUP);
  }

  void readJacks(uint8_t* output) {
    output[0] = digitalRead(JACK_PINS[0]);
    output[1] = digitalRead(JACK_PINS[1]);
    output[2] = digitalRead(JACK_PINS[2]);
  }

  int readMeter() {
    return analogRead(METER_PIN);
  }
};

ManualInput_ ManualInput;

#endif
