#ifndef CONTEXT_H
#define CONTEXT_H

#include "interface/SegmentDisplay.hpp"
#include "interface/ManualInput.hpp"
#include "interface/ChipManager.hpp"

struct Context {
    ManualInput input;
    SegmentDisplay display;
    ChipManager rfid;
};

#endif
