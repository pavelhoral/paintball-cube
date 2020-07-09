#ifndef CIPHERDEFUSE_HPP
#define CIPHERDEFUSE_HPP

#include "GameModule.hpp"
#include "../context.hpp"

#include "../interface/AudioOutput.hpp"
#include "../services/MelodyPlayer.hpp"
#include "../services/MelodyNotes.h"

class CipherDefuse : public GameModule {
public:
  CipherDefuse(Context context);
  void loop();
  void handleDefuse();
  void handleHint1();
  void handleHint2();
  void handleHint3();
  void handleWinner();
private:
  Context context_;
  uint8_t activeState_ = 255;
  boolean stateChange_;
  uint8_t hintState_ = 0;
  uint16_t defuseCode_ = 0;
  MelodyPlayer melodyPlayer_ = MelodyPlayer(BUZZER_PIN);
  uint8_t melodyDecode_ = 0;
  unsigned long errorTimer_ = 0;
  unsigned long morseStart_ = 0;
  uint8_t lastPosition_ = 0;
  uint8_t lastValue_ = -1;
  uint8_t codePosition_ = 0;
};

#endif
