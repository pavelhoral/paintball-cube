#include "ChipRegistry.hpp"

/**
 * Only support 32bit UID.
 */
const uint8_t UID_WIDTH = 4;

ChipRegistry::ChipRegistry(uint8_t maxCount, uint8_t dataWidth)
  : maxCount_(maxCount), dataWidth_(dataWidth)
{
  uidArray_ = (uint8_t*) malloc(maxCount_ * UID_WIDTH);
  dataArray_ = (uint8_t*) malloc(maxCount_ * dataWidth_);
}

void ChipRegistry::clear() {
  count_ = 0;
}

void ChipRegistry::put(byte* uid, byte* value) {
  if (count_ >= maxCount_) {
    return; // just ignore the call to prevent overflow
  }
  byte* currentData = get(uid);
  if (currentData) {
    memcpy(currentData, value, dataWidth_);
  } else {
    memcpy(uidArray_ + UID_WIDTH * count_, uid, UID_WIDTH);
    memcpy(dataArray_ + dataWidth_ * count_, value, dataWidth_);
    count_++;
  }
}

byte* ChipRegistry::get(byte* uid) {
  int index = indexOf(uid);
  return index >= 0 ? dataArray_ + index * dataWidth_ : 0;
}

int ChipRegistry::indexOf(byte* uid) {
  for (int i = 0; i < count_; i++) {
    int start = i * UID_WIDTH;
    bool match = true;
    for (int j = 0; j < UID_WIDTH; j++) {
      if (uidArray_[start + j] != uid[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      return i;
    }
  }
  return -1;
}
