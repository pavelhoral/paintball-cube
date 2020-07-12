#ifndef KEEPTALKING_HPP
#define KEEPTALKING_HPP

#include "../context.hpp"
#include "GameModule.hpp"

class KeepTalking : public GameModule {
public:
  KeepTalking(Context context);
  void setup();
  void loop();
private:
  Context context_;

  uint8_t gameIndex_ = 0;
  uint8_t lastJacks_ = 0;
  unsigned long lastBuzz_ = 0;

  uint16_t currentNumber_ = 0;

  void handleGame01();
  void handleGame02();
  void handleGame03();
  void handleGame04();
  void handleGame05();
  void handleError();
  void handleWinner();


  void handleCode(const uint16_t targetCode);
  void showLights(const uint8_t* sequence);
};

#endif
