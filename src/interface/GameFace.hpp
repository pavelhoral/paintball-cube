#ifndef GAMEFACE_H
#define GAMEFACE_H

#include <SPI.h>

#include "SegmentDisplay.hpp"
#include "ManualInput.hpp"
#include "ChipManager.hpp"

ManualInput_ ManualInput;
SegmentDisplay_ SegmentDisplay;
ChipManager_ ChipManager;

class GameFace_ {
public:
  void setup() {
    SPI.begin();
    ChipManager.setup();
  }
};

GameFace_ GameFace;

#endif
