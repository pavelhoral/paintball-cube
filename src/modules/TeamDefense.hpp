#ifndef TEAMDEFENSE_H
#define TEAMDEFENSE_H

#include "GameModule.hpp"
#include "../context.hpp"

struct ModuleConfig {
  // Time limit in seconds
  uint16_t timeLimit = 300;
};

/**
 * Team cube defence.
 * 
 * Team objective is to activate the cube and defend it during the clock countdown.
 */
class TeamDefense : public GameModule {
public:
  TeamDefense(Context context);
  void setup();
  void loop();
private:
  Context context_;
  ModuleConfig config_;
  uint8_t activeTeam_ = 0;
  unsigned long startTime_ = -1;
};

#endif
