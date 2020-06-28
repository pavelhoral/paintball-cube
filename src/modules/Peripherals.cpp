#include "Peripherals.hpp"

#include "../services/ChipRegistry.hpp"

ChipRegistry chipRegistry;

Peripherals::Peripherals(Context context) : context_(context) { }

void Peripherals::setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(9, HIGH);

  digitalWrite(3, LOW);
  delay(100);
  digitalWrite(3, HIGH);
}

void Peripherals::loop() {
  uint8_t jacks = context_.input.readJacks();
  context_.display.showNumberDec(jacks, true);

  analogWrite(6, context_.input.readMeter() * 24);
  analogWrite(5, 255 - context_.input.readMeter() * 24);

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

void Peripherals::teardown() {

}