#include "ManualInput.hpp"

const int METER_CUTOVER_LOW = 850;
const int METER_CUTOVER_HIGH = 980;

const int METER_DEBOUNCE_COUNT = 5;

struct {
  uint8_t stableValue = 0;
  uint8_t lastValue = 0;
  uint8_t lastStable = 0;
} MeterDebounce;

ManualInput_::ManualInput_() {
  pinMode(JACK_PINS[0], INPUT_PULLUP);
  pinMode(JACK_PINS[1], INPUT_PULLUP);
  pinMode(JACK_PINS[2], INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

uint8_t ManualInput_::readJacks() {
  return (digitalRead(JACK_PINS[0]) == LOW)
      | (digitalRead(JACK_PINS[1]) == LOW) << 1
      | (digitalRead(JACK_PINS[2]) == LOW) << 2;
}

uint8_t ManualInput_::readMeter() {
  long value = 1024 - analogRead(METER_PIN);
  if (value >= METER_CUTOVER_HIGH) {
    value = map(value, METER_CUTOVER_HIGH, 1024, 75, 100);
  } else if (value >= METER_CUTOVER_LOW) {
    value = map(value, METER_CUTOVER_LOW, METER_CUTOVER_HIGH, 45, 75);
  } else {
    value = map(value, 0, METER_CUTOVER_LOW, 0, 45);
  }
  value = (value + 5) / 10;
  if (MeterDebounce.lastValue != value) {
    MeterDebounce.lastValue = value;
    MeterDebounce.lastStable = 0;
  } else if (++MeterDebounce.lastStable >= METER_DEBOUNCE_COUNT) {
    MeterDebounce.stableValue = value;
  }
  return MeterDebounce.stableValue;
}

boolean ManualInput_::readSwitch() {
  return digitalRead(SWITCH_PIN) == LOW;
}
