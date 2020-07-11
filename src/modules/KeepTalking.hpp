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
  uint8_t hintIndex_ = 0;

  void handleGame01();
};

#endif
