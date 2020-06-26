#ifndef CHIPMANAGER_H
#define CHIPMANAGER_H

#include <Arduino.h>
#include <MFRC522.h>
#include <inttypes.h>

const uint8_t MFRC_SS_PIN = 10;
const uint8_t MFRC_RST_PIN = 8;

class ChipManager : public MFRC522 {
public:
  ChipManager() : MFRC522(MFRC_SS_PIN, MFRC_RST_PIN) {
  }

  /**
   * Initialize chip reader.
   */
  void setup();

  /**
   * Read chip number.
   */
  uint32_t readChip();
};

#endif
