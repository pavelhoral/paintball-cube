#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>

#include "context.hpp"

#include "services/ConfigSignals.hpp"

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
#include "modules/TeamDefense.hpp"
#include "modules/CipherDefuse.hpp"
#include "modules/GuessNumber.hpp"
#include "modules/KeepTalking.hpp"

/**
 * Create game module with the given index.
 */
GameModule* createModule(uint8_t index) {
  switch (index) {
    case 0: return new SystemTest(context);
    case 1: return new TeamDefense(context);
    case 2: return new CipherDefuse(context);
    case 3: return new GuessNumber(context);
    default: return NULL;
  }
}

#define SERIAL_MAGIC 58
#define SERIAL_OFFSET 4

/**
 * Persist configuration.
 */
void persist() {
  ConfigSignals::persist(context);
  EEPROM.put(SERIAL_OFFSET + 1, context.config);
  EEPROM.write(SERIAL_OFFSET, SERIAL_MAGIC);
}

/**
 * Select module with the specified index.
 */ 
boolean selectModule(uint8_t index, boolean save = false) {
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

  if (save) {
    context.config.moduleIndex = index;
    persist();
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
    EEPROM.get(SERIAL_OFFSET + 1, context.config);
  }

  if (context.rfid.readChip() == context.config.masterCard) {
    ConfigSignals::enter(context);
  } else {
    selectModule(context.config.moduleIndex);
  }
}

/**
 * Configuration loop.
 */
void configure() {
  uint32_t chipId = context.rfid.readChip();
  if (chipId == context.config.masterCard) {
    if (selectModule(state.moduleIndex, context.input.readJacks() == 2)) {
      ConfigSignals::confirm(context);
      return; // Exit configuration mode
    } else {
      ConfigSignals::cancel(context);
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
