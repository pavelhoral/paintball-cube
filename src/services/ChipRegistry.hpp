#ifndef CHIPREGISTRY_HPP
#define CHIPREGISTRY_HPP

#include <Arduino.h>

/**
 * Render UID to HEX stirng.
 */
String toHexUid(byte* uid);

/**
 * Chip card value registry mapping chip UIDs to arbitrary data.
 */
class ChipRegistry {
public:
  /**
   * Create new chip registry.
   */
  ChipRegistry(uint8_t maxCount = 64, uint8_t dataWidth = 1);

  /**
   * Clear all registered chips.
   */
  void clear();

  /**
   * Register new chip with the given value.
   */
  void put(byte* uid, byte* value);

  /**
   * Find registered value for the specified chip.
   */
  byte* get(byte* uid);

  /**
   * Get index of the specified chip within the registry.
   */
  int indexOf(byte* uid);

private:
  /**
   * Current number of registered chips.
   */
  uint8_t count_ = 0;

  /**
   * Chip registry capacity.
   */
  uint8_t maxCount_;

  /**
   * Registered data byte width.
   */
  uint8_t dataWidth_;

  /**
   * Array of registered chip UIDs.
   */
  byte* uidArray_;

  /**
   * Array of assigned chip data.
   */
  byte* dataArray_;
};

#endif
