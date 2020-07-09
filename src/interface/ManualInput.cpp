#include "ManualInput.hpp"

struct {
  boolean lastValue;
} SwitchState;

ManualInput::ManualInput() {
  pinMode(JACK_PINS[0], INPUT_PULLUP);
  pinMode(JACK_PINS[1], INPUT_PULLUP);
  pinMode(JACK_PINS[2], INPUT_PULLUP);

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  SwitchState.lastValue = digitalRead(SWITCH_PIN) == LOW;

  pinMode(METER_PIN, INPUT);
}

void ManualInput::reset() {
  readSwitch(); // Drop switch value
}

uint8_t ManualInput::readJacks() {
  return (digitalRead(JACK_PINS[0]) == LOW)
      | (digitalRead(JACK_PINS[1]) == LOW) << 1
      | (digitalRead(JACK_PINS[2]) == LOW) << 2;
}

uint8_t ManualInput::readMeter() {
  int rawValue = analogRead(METER_PIN) - 25;
  uint8_t result = rawValue / 100;
  if ((rawValue % 100 < 10) || (rawValue % 100) > 90) {
    if (abs(lastMeter_ - result) <= 1) {
      return lastMeter_;
    }
  }
  lastMeter_ = result;
  return result;
}

boolean ManualInput::readSwitch(boolean raw) {
  boolean value = digitalRead(SWITCH_PIN) == LOW;
  boolean change = SwitchState.lastValue != value;
  SwitchState.lastValue = value;
  return raw ? value : change;
}
