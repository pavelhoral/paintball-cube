#ifndef GAMEMODULE_H
#define GAMEMODULE_H

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
  virtual void setup() = 0;

  /**
   * Main loop module logic.
   */
  virtual void loop() = 0;
};

#endif
