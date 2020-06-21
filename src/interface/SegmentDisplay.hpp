#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

#define DISPLAY_PIN_CLK A4
#define DISPLAY_PIN_DIO A3
#define DISPLAY_BRIGHTNESS 30

class SegmentDisplay_ : public TM1637Display {
public:
  SegmentDisplay_() : TM1637Display(DISPLAY_PIN_CLK, DISPLAY_PIN_DIO) {
    setBrightness(DISPLAY_BRIGHTNESS);
  }
};

SegmentDisplay_ SegmentDisplay;

#endif
