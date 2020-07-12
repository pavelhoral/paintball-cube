#ifndef GUESSNUMBER_HPP
#define GUESSNUMBER_HPP

#include "GameModule.hpp"
#include "../context.hpp"

struct GuessNumberConfig {
  uint16_t targetNumber = 500;
  uint8_t allowedError = 0;
};

class GuessNumber : public GameModule {
public:
  GuessNumber(Context context);
  void setup();
  void loop();
private:
  Context context_;
  GuessNumberConfig moduleConfig_;
  uint8_t activeState_;
  uint8_t configState_;
  uint16_t currentNumber_ = 0;
  uint8_t currentLength_ = 1;

  void resetNumber();
  void handleGame();
  void handleConfig();
};

#endif
