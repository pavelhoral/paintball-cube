#include "CipherDefuse.hpp"

// HINT1 do re mi fa so la si do
// HINT2 morseovka
// HINT3 trezor

#define STATE_DEFUSE 0
#define STATE_HINT1 1
#define STATE_HINT2 2
#define STATE_HINT3 3
#define STATE_WINNER 4

#define DEFUSE_CODE 948

#define ERROR_SOUND 1, 2
#define WINNER_SOUND 1, 4

#define SCALE_TEMPO 1000

const int SCALE_MELODY[] = {
  NOTE_00, NOTE_2(SCALE_TEMPO),
  NOTE_C4, NOTE_2(SCALE_TEMPO),
  NOTE_D4, NOTE_2(SCALE_TEMPO),
  NOTE_E4, NOTE_2(SCALE_TEMPO),
  NOTE_F4, NOTE_2(SCALE_TEMPO),
  NOTE_G4, NOTE_2(SCALE_TEMPO),
  NOTE_A4, NOTE_2(SCALE_TEMPO),
  NOTE_B4, NOTE_2(SCALE_TEMPO),
  NOTE_C5, NOTE_2(SCALE_TEMPO)
};

uint8_t scalePosition(uint8_t value) {
  // 7 4 0 8 1 9 6 2
  switch (value) {
    case 0: return 0;
    case 1: return 5;
    case 2: return 8;
    case 3: return 6;
    case 4: return 2;
    case 5: return 3;
    case 6: return 7;
    case 7: return 1;
    case 8: return 4;
    case 9: return 0;
  }
  return 0;
}

uint8_t scaleDigit(uint8_t value) {
  switch (value) {
    case 0: return 0b00001000;
    case 1: return 0b00010000;
    case 2: return 0b00100000;
    case 3: return 0b00000001;
    case 4: return 0b00000010;
    case 5: return 0b00000100;
    case 6: return 0b00001000;
    case 7: return 0b00010000;
    case 8: return 0b00100000;
    case 9: return 0b00000001;
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
    stateChange_ = activeState_ != activeJack || activeState_ == 255;
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
    case STATE_HINT1:
      handleHint1();
      break;
    case STATE_HINT2:
      handleHint2();
      break;
    case STATE_HINT3:
      handleHint3();
      break;
    case STATE_WINNER:
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
      activeState_ = STATE_WINNER;
      stateChange_ = true;
      return;
    }
  }
  uint8_t digit = context_.input.readMeter();
  defuseCode_ = defuseCode_ - (defuseCode_ % 10) + digit;
  context_.display.showNumberDec(defuseCode_);
}

void CipherDefuse::handleHint1() {
  if (hintState_ & 1) {
    context_.display.showNumberDec(DEFUSE_CODE / 100, false, 1, 1);
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
  if (millis() - errorTimer_ < 500) {
    context_.light.setLevels(255, 0, 0);
  } else {
    context_.light.setLevels(0, 0, 255);
  }
  melodyPlayer_.update(millis());
  uint8_t input = context_.input.readMeter();
  if (input == 0 || input == 9) {
    context_.display.reset();
    return;
  }
  uint8_t digit = scaleDigit(input);
  if (digit != 0) {
    digit = context_.display.encodeDigit(input);
  }
  context_.display.setSegments(&digit, 1, 1);
  if (!context_.input.readSwitch()) {
    return; // no-input
  }
  errorTimer_ = 0;
  uint8_t toneIndex = scalePosition(context_.input.readMeter());
  if (melodyDecode_ + 1 == toneIndex) {
    melodyDecode_++;
  } else {
    melodyDecode_ = 0;
    if (toneIndex != 1) {
      errorTimer_ = millis();
    }
  }
  melodyPlayer_.load(&SCALE_MELODY[toneIndex * 2], 1);
  melodyPlayer_.play();
  if (melodyDecode_ == 8) {
    context_.audio.play(WINNER_SOUND);
    hintState_ |= 1;
  };
}

void CipherDefuse::handleHint2() {
  if (stateChange_ || context_.input.readSwitch()) {
    uint8_t dash = 0b01001001;
    context_.display.setSegments(&dash, 1, 2);
    context_.audio.buzz(100);
    delay(500);
    morseStart_ = millis();
    lastPosition_ = -1;
  }
  const String code = "- . - . / - / - . - - / . - . / . . / /";
  uint8_t position = (millis() - morseStart_) / 500;
  if (position > 39) {
    context_.light.reset();
    return;
  } else if (position == 39) {
    context_.audio.buzz(200);
  }
  if (lastPosition_ != position) {
    lastPosition_ = position;
    context_.audio.buzz(10);
    switch (code[position]) {
      case '/':
        context_.light.setLevels(255, 0, 0);
        break;
      case '.':
        context_.light.setLevels(0, 255, 0);
        break;
      case '-':
        context_.light.setLevels(0, 0, 255);
        break;
      case ' ':
        context_.light.setLevels(0, 0, 0);
        break;
    }
  }
}

const uint8_t HINT3_CODE[] = { 6, 4, 9, 3, 8, 1, 5 };

void CipherDefuse::handleHint3() {
  if (hintState_ & 4) {
    context_.light.setLevels(0, 255, 0);
    context_.display.showNumberDec(DEFUSE_CODE % 10);
    melodyPlayer_.update(millis());
    return;
  }
  if (stateChange_) {
    context_.light.setLevels(0, 0, 255);
  }
  uint8_t value = context_.input.readMeter();
  uint8_t digit = context_.display.encodeDigit(value);
  context_.display.setSegments(&digit, 1, 3);

  boolean clockwise = codePosition_ % 2 == 1;
  uint8_t target = HINT3_CODE[codePosition_];

  if (value == target) {
    context_.audio.buzz(50);
    codePosition_++;
  } else if (((clockwise && lastValue_ < value) || (!clockwise && lastValue_ > value)) && codePosition_ != 0) {
    context_.light.setLevels(255, 0, 0);
    context_.audio.buzz(250);
    context_.light.setLevels(0, 0, 255);
    codePosition_ = 0;
  } else if (lastValue_ != value) {
    context_.audio.buzz(5);
  }
  lastValue_ = value;
  if (codePosition_ >= 7) {
    context_.audio.play(WINNER_SOUND);
    hintState_ |= 4;
  }
}

void CipherDefuse::handleWinner() {
  if (stateChange_) {
    context_.light.setLevels(0, 255, 0);
    context_.display.showNumberDec(0, true);
    context_.audio.play(1, 1);
  }
  stateChange_ = false;
}
