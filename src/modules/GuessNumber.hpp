#ifndef GUESSNUMBER_HPP
#define GUESSNUMBER_HPP

#include "GameModule.hpp"
#include "../context.hpp"

class GuessNumber : public GameModule {
public:
  GuessNumber(Context context);
  void setup();
  void loop();
private:
  Context context_;
  uint8_t activeState_;
  uint16_t targetNumber_;
  uint16_t currentNumber_;
  uint8_t allowedError_ = 2;
};

#endif
