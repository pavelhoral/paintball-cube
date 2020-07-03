#include "SystemTest.hpp"

#include "../services/ChipRegistry.hpp"

ChipRegistry chipRegistry;

SystemTest::SystemTest(Context context) : context_(context) { }

void SystemTest::setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  digitalWrite(3, LOW);
  delay(100);
  digitalWrite(3, HIGH);

  chipRegistry.clear();
}

void SystemTest::loop() {
  context_.display.showNumberDec(context_.input.readMeter(), true);

  uint8_t jacks = context_.input.readJacks();
  context_.light.setLevels((jacks & 1) * 255, (jacks >> 1 & 1) * 255, (jacks >> 2 & 1) * 255);

  if (context_.input.readSwitch()) {
    //context_.audio.volume(30);
    //context_.audio.play(1);
  }
  //context_.audio.available();

  uint32_t chipUid = context_.rfid.readChip();
  if (chipUid != 0) {
    uint8_t value = 0;
    chipRegistry.put((byte *) &chipUid, &value);
    int cardIdx = chipRegistry.indexOf((byte *) &chipUid);
    context_.display.showNumberDec(cardIdx);
    digitalWrite(3, LOW);
    delay(100);
    digitalWrite(3, HIGH);
    delay(200);
  }
}