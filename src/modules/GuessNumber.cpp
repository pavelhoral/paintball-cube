#include "GuessNumber.hpp"
#include <EEPROM.h>
#include "../services/ConfigSignals.hpp"

#define SERIAL_MAGIC 66
#define SERIAL_OFFSET 20

#define STATE_GAME 0
#define STATE_CONFIG 1
#define STATE_WINNER 2

#define ERROR_SOUND 1, 2
#define WINNER_SOUND 1, 4

GuessNumber::GuessNumber(Context context) : context_(context) {
}

void GuessNumber::setup() {
  activeState_ = STATE_GAME;
  if (EEPROM.read(SERIAL_OFFSET) == SERIAL_MAGIC) {
    EEPROM.get(SERIAL_OFFSET + 1, moduleConfig_);
  }
}

const uint8_t WINNER_SEGMENTS[] = { 0b01001001, 0b01001001, 0b01001001, 0b01001001 };

void GuessNumber::loop() {
  switch (activeState_) {
    case STATE_WINNER:
      context_.display.setSegments(WINNER_SEGMENTS, 4);
      context_.light.setLevels(0, 255, 0);
      break;
    case STATE_GAME:
      handleGame();
      break;
    case STATE_CONFIG:
      handleConfig();
      break;
  }
}

void GuessNumber::resetNumber() {
  context_.display.clear();
  currentNumber_ = 0;
  currentLength_ = 1;
}

void GuessNumber::handleConfig() {
  if (configState_ == 0) {
    configState_ = 1;
    resetNumber();
    context_.audio.buzz(50);
    context_.light.setLevels(0, 0, 255);
    return;
  }
  if (context_.input.readSwitch()) {
    context_.audio.buzz(50);
    if (currentLength_ < 4) {
      currentLength_++;
      currentNumber_ *= 10;
    } else {
      resetNumber();
    }
  }
  uint8_t digit = context_.input.readMeter();
  currentNumber_ = currentNumber_ - (currentNumber_ % 10) + digit;
  context_.display.showNumberDec(currentNumber_, true, currentLength_);
  if (context_.rfid.readChip() == context_.config.masterCard) {
    if (configState_ == 1) {
      context_.audio.buzz(50);
      moduleConfig_.targetNumber = currentNumber_;
      configState_ = 2;
      resetNumber();
    } else {
      moduleConfig_.allowedError = currentNumber_;
      activeState_ = STATE_GAME;
      resetNumber();
      if (context_.input.readJacks() != 0) {
        ConfigSignals::persist(context_);
        EEPROM.put(SERIAL_OFFSET, SERIAL_MAGIC);
        EEPROM.put(SERIAL_OFFSET + 1, moduleConfig_);
      } else {
        context_.audio.buzz(250);
      }
    }
  }
}

void GuessNumber::handleGame() {
  if (context_.rfid.readChip() == context_.config.masterCard) {
    activeState_ = STATE_CONFIG;
    configState_ = 0;
    return;
  }
  context_.light.setLevels(255, 0, 0);
  boolean enter = context_.input.readSwitch();
  if (enter) {
    uint16_t lowerBound = moduleConfig_.targetNumber - moduleConfig_.allowedError;
    uint16_t upperBound = moduleConfig_.targetNumber + moduleConfig_.allowedError;
    if (currentLength_ < 4) {
      context_.audio.buzz(50);
      currentNumber_ *= 10;
      currentLength_++;
    } else if (currentNumber_ >= lowerBound && currentNumber_ <= upperBound) {
      context_.audio.play(WINNER_SOUND);
      activeState_ = STATE_WINNER;
      return;
    } else {
      context_.audio.play(ERROR_SOUND);
      resetNumber();
    }
  }
  uint8_t digit = context_.input.readMeter();
  currentNumber_ = currentNumber_ - (currentNumber_ % 10) + digit;
  context_.display.showNumberDec(currentNumber_, true, currentLength_);
}
