#include "TeamDefense.hpp"

uint8_t readTeam(Context &context) {
  uint8_t jacks = context.input.readJacks();
  switch (jacks) {
    case 1: return 1;
    case 2: return 2;
    case 4: return 3;
    default: return 0;
  }
}

void displayTime(Context &context, uint16_t time) {
  context.display.showNumberDecEx(time / 60 * 100 + time % 60, 0b01000000, true);
}

TeamDefense::TeamDefense(Context context) : context_(context) {
}

void TeamDefense::setup() {
}

void TeamDefense::loop() {
  unsigned long currentTime = millis();

  uint8_t currentTeam = readTeam(context_);
  if (currentTeam != activeTeam_) {
    activeTeam_ = currentTeam;
    startTime_ = currentTime;
  }

  if (activeTeam_ == 0) {
    context_.light.setLevels(0, 255, 0);
    displayTime(context_, config_.timeLimit);
    return;
  } else {
    context_.light.setLevels(255, 0, 0);
  }

  int remaining = config_.timeLimit - (currentTime - startTime_) / 1000;
  if (remaining > 0) {
    displayTime(context_, remaining);
  }

  if (remaining < 0) {
    context_.display.showNumberDec(currentTeam);
    boolean switchValue = context_.input.readSwitch(true);
    while (switchValue == context_.input.readSwitch(true)) {
      context_.audio.buzz(500);
      context_.light.setLevels(255, 127, 127);
      delay(500);
      context_.light.setLevels(0, 0, 0);
    }
  }
}
