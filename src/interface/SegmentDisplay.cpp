#include "SegmentDisplay.hpp"

SegmentDisplay::SegmentDisplay() : TM1637Display(DISPLAY_PIN_CLK, DISPLAY_PIN_DIO) {
    reset();
}

void SegmentDisplay::reset() {
    clear();
    setBrightness(DISPLAY_BRIGHTNESS);
}
