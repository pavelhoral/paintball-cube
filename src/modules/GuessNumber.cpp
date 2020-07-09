#include "GuessNumber.hpp"
#include <EEPROM.h>
#include "../services/ConfigSignals.hpp"

#define SERIAL_OFFSET 20

#define STATE_GAME 0
#define STATE_WINNER 1

#define ERROR_SOUND 1, 2
#define WINNER_SOUND 1, 4

GuessNumber::GuessNumber(Context context) : context_(context) {
}

void GuessNumber::setup() {
  activeState_ = STATE_GAME;
  currentNumber_ = 0;
  EEPROM.get(SERIAL_OFFSET + 1, targetNumber_);
}


void GuessNumber::loop() {
  if (activeState_ == STATE_WINNER) {
    context_.display.showNumberDec(0, true);
    return;
  }
  boolean enter = context_.input.readSwitch();
  if (enter) {
    boolean final = currentNumber_ > 99;
    if (!final) {
      context_.audio.buzz(50);
      currentNumber_ *= 10;
    } else if (currentNumber_ >= targetNumber_ - allowedError_ && currentNumber_ <= targetNumber_ + allowedError_) {
      context_.audio.play(WINNER_SOUND);
      activeState_ = STATE_WINNER;
      return;
    } else {
      context_.audio.play(ERROR_SOUND);
      currentNumber_ = 0;
    }
  }
  uint8_t digit = context_.input.readMeter();
  currentNumber_ = currentNumber_ - (currentNumber_ % 10) + digit;
  if (context_.rfid.readChip() == context_.config.masterCard) {
    targetNumber_ = currentNumber_;
    currentNumber_ = 0;
    ConfigSignals::persist(context_);
    EEPROM.put(SERIAL_OFFSET + 1, targetNumber_);
  }
  context_.display.showNumberDec(currentNumber_);
}
