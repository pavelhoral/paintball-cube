#include "Peripherals.hpp"

#include "../interface/SegmentDisplay.hpp"
#include "../interface/ManualInput.hpp"

Peripherals::Peripherals() { }

void Peripherals::setup() {
}

const int METER_CUTOVER_LOW = 850;
const int METER_CUTOVER_HIGH = 980;

const int METER_DEBOUNCE_COUNT = 5;

int lastMeter = 0;
int meterDebounce = 0;

void Peripherals::loop() {
  // unsigned long time = millis();
  // SegmentDisplay.showNumberDec(time / 1000, true);
  long value = 1024 - ManualInput.readMeter();
  if (value >= METER_CUTOVER_HIGH) {
    value = map(value, METER_CUTOVER_HIGH, 1024, 75, 100);
  } else if (value >= METER_CUTOVER_LOW) {
    value = map(value, METER_CUTOVER_LOW, METER_CUTOVER_HIGH, 45, 75);
  } else {
    value = map(value, 0, METER_CUTOVER_LOW, 0, 45);
  }
  value = (value + 5) / 10;
  if (lastMeter != value) {
      lastMeter = value;
      meterDebounce = 0;
  } else if (++meterDebounce >= METER_DEBOUNCE_COUNT) {
    SegmentDisplay.showNumberDec(value);
  }
}

void Peripherals::teardown() {

}