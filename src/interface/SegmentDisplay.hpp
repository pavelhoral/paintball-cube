#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

const uint8_t DISPLAY_PIN_CLK = A4;
const uint8_t DISPLAY_PIN_DIO = A3;
const uint8_t DISPLAY_BRIGHTNESS = 30;

class SegmentDisplay : public TM1637Display {
public:
  SegmentDisplay() : TM1637Display(DISPLAY_PIN_CLK, DISPLAY_PIN_DIO) {
    setBrightness(DISPLAY_BRIGHTNESS);
  }
};

#endif
