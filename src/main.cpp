#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>

#include "context.hpp"

/**
 * I/O context.
 */ 
Context context;

#include "modules/GameModule.hpp"

/**
 * Currently loaded game module.
 */
GameModule* module = NULL;

#include "modules/SystemTest.hpp"

/**
 * Create game module with the given index.
 */
GameModule* createModule(uint8_t index) {
  switch (index) {
    case 0: return new SystemTest(context);
    default: return NULL;
  }
}

#define SERIAL_MAGIC 58
#define SERIAL_OFFSET 4

struct CubeConfig {
  uint32_t masterCard = 3002390521;
  uint8_t moduleIndex = 0;
};

CubeConfig config;

/**
 * Select module with the specified index.
 */ 
boolean selectModule(uint8_t index) {
  if (module != NULL) {
    delete module;
  }

  context.audio.reset();
  context.display.reset();
  context.input.reset();
  context.light.reset();

  module = createModule(index);
  if (module == NULL) {
    return false;
  }
  module->setup();
  return true;
}

struct {
  int moduleIndex = 0;
} state;

/**
 * Cube bootstrap.
 */
void setup() {
  SPI.begin();
  context.rfid.setup();
  Serial.begin(9600);
  context.audio.setup(Serial);

  if (EEPROM.read(SERIAL_OFFSET) == SERIAL_MAGIC) {
    EEPROM.get(SERIAL_OFFSET, config);
  }

  if (context.rfid.readChip() == config.masterCard) {
    context.audio.play(1, 1);
  } else {
    selectModule(config.moduleIndex);
  }
}

/**
 * Configuration loop.
 */
void configure() {
  uint32_t chipId = context.rfid.readChip();
  if (chipId == config.masterCard) {
    if (selectModule(state.moduleIndex)) {
      context.audio.buzz(250);
      return; // Exit configuration mode
    } else {
      context.audio.buzz(100, 2, 50);
      state.moduleIndex = 0;
    }
  }

  if (context.input.readSwitch()) { // Add another digit
    state.moduleIndex *= 10;
  }
  if (state.moduleIndex > 999) { // Reset if too large
    state.moduleIndex = 0;
  }
  state.moduleIndex = state.moduleIndex - (state.moduleIndex % 10) + context.input.readMeter();
  context.display.showNumberDec(state.moduleIndex);

}

/**
 * Main cube loop.
 */
void loop() {
  if (module != NULL) {
    module->loop();
  } else {
    configure();
  }
}
