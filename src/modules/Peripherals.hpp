#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include "GameModule.hpp"

/**
 * Peripherals tester module.
 */
class Peripherals : public GameModule {
public:
  Peripherals();
  void setup();
  void loop();
  void teardown();
};

#endif
