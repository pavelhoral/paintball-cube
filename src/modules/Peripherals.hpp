#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "GameModule.hpp"
#include "../context.hpp"

/**
 * Peripherals tester module.
 */
class Peripherals : public GameModule {
public:
  Peripherals(Context context);
  void setup();
  void loop();
  void teardown();
private:
  Context context_;
};

#endif
