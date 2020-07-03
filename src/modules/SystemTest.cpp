#include "SystemTest.hpp"

#include "../services/ChipRegistry.hpp"

ChipRegistry chipRegistry;

SystemTest::SystemTest(Context context) : context_(context) {
}

void SystemTest::setup() {
  chipRegistry.clear();
}

void SystemTest::loop() {
  context_.display.showNumberDec(context_.input.readMeter(), true);

  uint8_t jacks = context_.input.readJacks();
  context_.light.setLevels((jacks & 1) * 255, (jacks >> 1 & 1) * 255, (jacks >> 2 & 1) * 255);

  if (context_.input.readSwitch()) {
    context_.audio.play(1, 1);
  }
  context_.audio.update();

  uint32_t chipUid = context_.rfid.readChip();
  if (chipUid != 0) {
    uint8_t value = 0;
    chipRegistry.put((byte *) &chipUid, &value);
    int cardIdx = chipRegistry.indexOf((byte *) &chipUid);
    context_.audio.buzz(50);
    context_.display.showNumberDec(cardIdx);
  }
}
