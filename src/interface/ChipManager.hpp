#ifndef CHIPMANAGER_HPP
#define CHIPMANAGER_HPP

#include <Arduino.h>
#include <MFRC522.h>
#include <inttypes.h>

const uint8_t MFRC_SS_PIN = 10;

const uint8_t MFRC_RST_PIN = 8;

class ChipManager : public MFRC522 {
public:
  ChipManager();

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
