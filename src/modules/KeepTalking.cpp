#include "KeepTalking.hpp"

// 1 - 438
// 2 - 720
// 3 - 359
// 4 - 267
// 5 - 482

#define ERROR_SOUND 1, 2
#define WINNER_SOUND 1, 4

KeepTalking::KeepTalking(Context context) : context_(context) {
}

void KeepTalking::setup() {
  lastJacks_ = context_.input.readJacks();
}

void KeepTalking::loop() {
  switch (gameIndex_ + 1) {
    case 1:
      handleGame01();
      break;
    case 2:
      handleGame02();
      break;
    case 3:
      handleGame03();
      break;
    case 4:
      handleGame04();
      break;
    case 5:
      handleGame05();
      break;
    default:
      handleWinner();
  }
}

void KeepTalking::handleGame01() {
  // - STATE: LED blika cervena, zelena, zelena
  // - INTERACTION: na zasunuti konektoru zahraje nejaky nastroj
  // - ANSWER: je nutne zadat trojmistne cislo
  const uint8_t LIGHT_SIGNAL[] = { 0b00000100, 0b00000010, 0b00000010 };

  const uint8_t jacks = context_.input.readJacks();
  if (jacks != lastJacks_) {
    if (jacks > 0) {
      context_.light.setLevels(40, 40, 40);
      context_.display.clear();
    }
    switch (jacks) {
      case 1:
        context_.audio.play(2, 1); // dubstep - 4
        break;
      case 2:
        context_.audio.play(2, 4); // harfa - 3
        break;
      case 4:
        context_.audio.play(2, 6); // kytara - 8
        break;
      default:
        context_.audio.stop();
    }
    currentNumber_ = 0;
    context_.input.readSwitch();
    lastJacks_ = jacks;
  }

  if (jacks == 0) {
    showLights(LIGHT_SIGNAL);
    handleCode(438);
  }
}

void KeepTalking::handleGame02() {
  // - STATE: LED blika cervena, modra, modra
  // - INTERACTION: na zasunuti konektoru zahraje zvuk zvirete
  // - ANSWER: podle barvy diody je nutne zahrat za sebou zvuky tri zvirat pri zasunutem libovolnem jacku
  const uint8_t LIGHT_SIGNAL[] = { 0b00000100, 0b00000001, 0b00000001 };

  const uint8_t jacks = context_.input.readJacks();
  if (jacks != lastJacks_) {
    if (jacks > 0) {
      context_.light.setLevels(40, 40, 40);
      context_.display.clear();
    }
    switch (jacks) {
      case 1:
        context_.audio.play(3, 2); // pav - 7
        break;
      case 2:
        context_.audio.play(3, 7); // hyena - 2
        break;
      case 4:
        context_.audio.play(3, 8); // delfin - 0
        break;
      default:
        context_.audio.stop();
    }
    currentNumber_ = 0;
    context_.input.readSwitch();
    lastJacks_ = jacks;
  }

  if (jacks == 0) {
    showLights(LIGHT_SIGNAL);
    handleCode(720);
  }
}

void KeepTalking::handleGame03() {
  // - STATE: LED blika cervena, zelena, modra
  // - INTERACTION: na zasunuti konektoru zahraje muziku
  // - ANSWER: podle barvy diody je nutne zahrat za sebou zvuky tri zvirat pri zasunutem libovolnem jacku
  const uint8_t LIGHT_SIGNAL[] = { 0b00000100, 0b00000010, 0b00000001 };

  const uint8_t jacks = context_.input.readJacks();
  if (jacks != lastJacks_) {
    if (jacks > 0) {
      context_.light.setLevels(40, 40, 40);
      context_.display.clear();
    }
    switch (jacks) {
      case 1:
        context_.audio.play(4, 2); // hraci skrinka - 3
        break;
      case 2:
        context_.audio.play(4, 4); // orchestr - 5
        break;
      case 4:
        context_.audio.play(4, 5); // elektronicka hudba - 9
        break;
      default:
        context_.audio.stop();
    }
    currentNumber_ = 0;
    context_.input.readSwitch();
    lastJacks_ = jacks;
  }

  if (jacks == 0) {
    showLights(LIGHT_SIGNAL);
    handleCode(359);
  }
}

void KeepTalking::handleGame04() {
  // - STATE: LED blika zelena, modra, modra
  // - INTERACTION: na zasunuti konektoru ukaze symbol
  // - ANSWER: podle symbolu je nutne zadat cislo
  const uint8_t LIGHT_SIGNAL[] = { 0b00000100, 0b00000001, 0b00000001 };

  const uint8_t jacks = context_.input.readJacks();
  if (jacks != lastJacks_) {
    if (jacks > 0) {
      context_.light.setLevels(40, 40, 40);
      context_.display.clear();
    }
    uint8_t segments[] = { 0, 0, 0, 0 };
    switch (jacks) {
      case 1:
        segments[2] = 0b00001100; // pravy spodni roh na treti pozici - 2
        break;
      case 2:
        segments[1] = 0b00100010; // dve vertikalni cary na druhe pozici - 6
        break;
      case 4:
        segments[3] = 0b01000000; // pomlcka na ctvrte pozici - 7
        break;
    }
    context_.display.setSegments(segments);
    currentNumber_ = 0;
    context_.input.readSwitch();
    lastJacks_ = jacks;
  }

  if (jacks == 0) {
    showLights(LIGHT_SIGNAL);
    handleCode(267);
  }
}

void KeepTalking::handleGame05() {
  // - STATE: LED blika cervena, cervena, modra
  // - INTERACTION: na zasunuti konektoru ukaze symbol
  // - ANSWER: podle symbolu je nutne zadat cislo
  const uint8_t LIGHT_SIGNAL[] = { 0b00000100, 0b00000100, 0b00000001 };

  const uint8_t jacks = context_.input.readJacks();
  if (jacks != lastJacks_) {
    if (jacks > 0) {
      context_.light.setLevels(40, 40, 40);
      context_.display.clear();
    }
    uint8_t segments[] = { 0, 0, 0, 0 };
    switch (jacks) {
      case 1:
        segments[3] = 0b00111100; // zhasnuty pravy horni roh na ctvrte pozici - 4
        break;
      case 2:
        segments[2] = 0b00110011; // zhasnuty spodni pravy roh na treti pozici - 8
        break;
      case 4:
        segments[0] = 0b01010101; // neuplne pismeno A na prvni pozici - 2
        break;
    }
    context_.display.setSegments(segments);
    currentNumber_ = 0;
    context_.input.readSwitch();
    lastJacks_ = jacks;
  }

  if (jacks == 0) {
    showLights(LIGHT_SIGNAL);
    handleCode(482);
  }
}

void KeepTalking::handleError() {
  for (int i = 10; i > 0; i--) {
    context_.display.showNumberDec(i, true);
    for (int j = 0; j < 10; j++) {
      context_.light.setLevels(255, 0, 0);
      delay(50);
      context_.light.setLevels(0, 0, 0);
      context_.audio.buzz(5);
      delay(45);
    }
  }
  context_.input.readSwitch();
  currentNumber_ = 0;
}

void KeepTalking::handleWinner() {
  if (gameIndex_ == 5) {
    context_.light.setLevels(0, 255, 0);
    context_.display.showNumberDec(0, true);
    context_.audio.play(1, 1);
    gameIndex_++;
  }
}

void KeepTalking::showLights(const uint8_t* sequence) {
  unsigned long time = millis();
  if (time % 1000 > 500) {
    context_.light.reset();
  } else {
    uint8_t lights = sequence[(time / 1000) % 3];
    context_.light.setLevels(
        (lights >> 2) % 2 * 255,
        (lights >> 1) % 2 * 255,
        (lights % 2) * 255);
    if (time - time % 1000 > lastBuzz_) {
      lastBuzz_ = time - time % 1000;
      context_.audio.buzz(10);
    }
  }
}

void KeepTalking::handleCode(const uint16_t targetCode) {
  currentNumber_ = currentNumber_ - (currentNumber_ % 10) + context_.input.readMeter();
  context_.display.showNumberDec(currentNumber_);
  if (!context_.input.readSwitch()) {
    return;
  }
  context_.audio.buzz(50);
  if (currentNumber_ > 99 && currentNumber_ != targetCode) {
    handleError();
  } else if (currentNumber_ <= 99) {
    currentNumber_ *= 10;
  } else {
    context_.audio.play(WINNER_SOUND);
    currentNumber_ = 0;
    gameIndex_++;
  }
}
