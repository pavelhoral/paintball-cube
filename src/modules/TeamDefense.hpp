#ifndef TEAMDEFENSE_HPP
#define TEAMDEFENSE_HPP

#include "GameModule.hpp"
#include "../context.hpp"

struct TeamDefenseConfig {
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
  TeamDefenseConfig config_;
  boolean configMode_ = 0;
  uint8_t activeTeam_ = 0;
  uint8_t stopDebounce_;
  unsigned long startTime_ = -1;
  void handleGame();
  void handleConfig();
};

#endif
