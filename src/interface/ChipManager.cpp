#include "ChipManager.hpp"

uint32_t ChipManager_::readChip() {
  if (!PICC_IsNewCardPresent() || !PICC_ReadCardSerial()) {
    return 0;
  }
  PICC_HaltA();
  void* uidPtr = uid.uidByte;
  return *((uint32_t *) uidPtr);
}
