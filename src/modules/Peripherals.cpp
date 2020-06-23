#include "Peripherals.hpp"

#include "../interface/GameFace.hpp"
#include "../services/ChipRegistry.hpp"

ChipRegistry_ ChipRegistry;

Peripherals::Peripherals() { }

void Peripherals::setup() {
  pinMode(3, OUTPUT);
}

void Peripherals::loop() {
  SegmentDisplay.showNumberDec(ManualInput.readSwitch(), true);

/*
  uint32_t chipUid = GameFace.ChipManager.readChip();
  if (chipUid != 0) {
    uint8_t value = 0;
    ChipRegistry.put((byte *) &chipUid, &value);
    int cardIdx = ChipRegistry.indexOf((byte *) &chipUid);
    GameFace.SegmentDisplay.showNumberDec(cardIdx);
    Serial.println("READ");
    digitalWrite(3, LOW);
    delay(100);
    digitalWrite(3, HIGH);
  }
*/
}

void Peripherals::teardown() {

}