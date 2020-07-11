#ifndef GAMEMODULE_HPP
#define GAMEMODULE_HPP

/**
 * Common parent class for all game modules.
 * Module lifecycle is pretty much similar the main class except for an aditional teardown logic.
 */
class GameModule {
public:
  virtual ~GameModule();

  /**
   * Standard module setup.
   */
  virtual void setup();

  /**
   * Main loop module logic.
   */
  virtual void loop() = 0;
};

#endif
