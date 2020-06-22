#include "Peripherals.hpp"

#include "../interface/SegmentDisplay.hpp"
#include "../interface/ManualInput.hpp"

#include "../interface/ChipManager.hpp"
#include "../services/ChipRegistry.hpp"

ManualInput_ ManualInput;
SegmentDisplay_ SegmentDisplay;
ChipManager_ ChipManager;
ChipRegistry_ ChipRegistry;

Peripherals::Peripherals() { }

void Peripherals::setup() {
  ChipManager.PCD_Init();
  pinMode(3, OUTPUT);
}

void Peripherals::loop() {
  // SegmentDisplay.showNumberDec(ManualInput.readSwitch(), true);

  uint32_t chipUid = ChipManager.readChip();
  if (chipUid != 0) {
    uint8_t value = 0;
    ChipRegistry.put((byte *) &chipUid, &value);
    int cardIdx = ChipRegistry.indexOf((byte *) &chipUid);
    SegmentDisplay.showNumberDec(cardIdx);
    Serial.println("READ");
    digitalWrite(3, LOW);
    delay(100);
    digitalWrite(3, HIGH);
  }
}

void Peripherals::teardown() {

}