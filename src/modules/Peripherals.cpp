#include "Peripherals.hpp"

#include "../interface/SegmentDisplay.hpp"
#include "../interface/ManualInput.hpp"

ManualInput_ ManualInput;
SegmentDisplay_ SegmentDisplay;

Peripherals::Peripherals() { }

void Peripherals::setup() {
}

void Peripherals::loop() {
  // unsigned long time = millis();
  SegmentDisplay.showNumberDec(ManualInput.readSwitch(), true);
}

void Peripherals::teardown() {

}