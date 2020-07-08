#include "CipherDefuse.hpp"

#define STATE_DEFUSE 0
#define STATE_HINT1 1
#define STATE_HINT2 2
#define STATE_HINT3 3
#define STATE_WINNER 4

#define DEFUSE_CODE 947

#define ERROR_SOUND 1, 2
#define WINNER_SOUND 1, 4

#define SCALE_TEMPO 1000

const int SCALE_MELODY[] = {
  NOTE_00, NOTE_2(SCALE_TEMPO),
  NOTE_C3, NOTE_2(SCALE_TEMPO),
  NOTE_D3, NOTE_2(SCALE_TEMPO),
  NOTE_E3, NOTE_2(SCALE_TEMPO),
  NOTE_F3, NOTE_2(SCALE_TEMPO),
  NOTE_G3, NOTE_2(SCALE_TEMPO),
  NOTE_A3, NOTE_2(SCALE_TEMPO),
  NOTE_B3, NOTE_2(SCALE_TEMPO),
  NOTE_C4, NOTE_2(SCALE_TEMPO)
};

uint8_t scalePosition(uint8_t value) {
  // 7 4 0 8 1 9 6 2
  switch (value) {
    case 0: return 3;
    case 1: return 5;
    case 2: return 8;
    case 3: return 0;
    case 4: return 2;
    case 5: return 0;
    case 6: return 7;
    case 7: return 1;
    case 8: return 4;
    case 9: return 6;
  }
  return 0;
}

CipherDefuse::CipherDefuse(Context context) : context_(context) {
}

void CipherDefuse::loop() {
  uint8_t activeJack = 0;
  switch (context_.input.readJacks()) {
    case 1:
      activeJack = 1;
      break;
    case 2:
      activeJack = 2;
      break;
    case 4:
      activeJack = 3;
      break;
  }

  if (activeState_ != STATE_WINNER) {
    stateChange_ = activeState_ != activeJack;
    activeState_ = activeJack;
  }

  if (stateChange_) {
    context_.audio.reset();
    context_.display.reset();
    context_.light.reset();
    context_.input.reset();
    melodyPlayer_.stop();
  }

  switch (activeState_) {
    case 0:
      handleDefuse();
      break;
    case 1:
      handleHint1();
      break;
    case 2:
      handleHint2();
      break;
    case 3:
      handleHint3();
      break;
    case 4:
      handleWinner();
      break;
  }  
}

void CipherDefuse::handleDefuse() {
  if (stateChange_) {
    defuseCode_ = 0;
    context_.light.setLevels(255, 0, 0);
    errorTimer_ = 0;
  }
  if (millis() - errorTimer_ > 1000) {
    errorTimer_ = millis();
    context_.audio.buzz(5);
  }
  if (hintState_ != 7) {
    return;
  }
  boolean enter = context_.input.readSwitch();
  if (enter) {    
    if (defuseCode_ > 99 && defuseCode_ != DEFUSE_CODE) {
      context_.audio.play(ERROR_SOUND);
      delay(2000);
      defuseCode_ = 0;
    } else if (defuseCode_ <= 99) {
      context_.audio.buzz(50);
      defuseCode_ *= 10;
    } else {
      context_.audio.play(WINNER_SOUND);
      activeState_ = STATE_WINNER;
      return;
    }
  }
  uint8_t digit = context_.input.readMeter();
  defuseCode_ = defuseCode_ - (defuseCode_ % 10) + digit;
  context_.display.showNumberDec(defuseCode_);
}

void CipherDefuse::handleHint1() {
  if (hintState_ & 1) {
    context_.display.showNumberDec(DEFUSE_CODE / 100);
    context_.light.setLevels(0, 255, 0);
    melodyPlayer_.update(millis());
    return;
  }
  if (stateChange_) {
    context_.audio.buzz(50);
    melodyPlayer_.load(SCALE_MELODY, 9);
    melodyPlayer_.play();
    melodyDecode_ = 0;
  }
  if (millis() - errorTimer_ < 1000) {
    context_.light.setLevels(255, 0, 0);
  } else {
    context_.light.reset();
  }
  melodyPlayer_.update(millis());
  uint8_t input = context_.input.readMeter();
  context_.display.showNumberDec(input, true);
  if (!context_.input.readSwitch()) {
    return; // no-input
  }
  errorTimer_ = 0;
  uint8_t tone = scalePosition(context_.input.readMeter());
  if (melodyDecode_ + 1 == tone) {
    melodyDecode_++;
  } else {
    errorTimer_ = millis();
    melodyDecode_ = tone == 1 ? 1 : 0;
  }
  melodyPlayer_.load(&SCALE_MELODY[tone * 2], 1);
  melodyPlayer_.play();
  if (melodyDecode_ == 8) {
    context_.audio.play(WINNER_SOUND);
    hintState_ |= 1;
  };
}

void CipherDefuse::handleHint2() {
// druhy jack: barvy jako morseovka - cisla, ktera je nutne zadat pro dalsi level
}

void CipherDefuse::handleHint3() {
// treti jack: potenciometr jako trezor
}

void CipherDefuse::handleWinner() {
  if (stateChange_) {
    context_.light.setLevels(0, 255, 0);
    delay(500);
    context_.audio.play(1, 1);
  }
}
