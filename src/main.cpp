#include <Arduino.h>
#include <TM1637Display.h>
#include <MFRC522.h>
#include <EEPROM.h>

#include "ChipRegistry.hpp"

//~ PIN Constants

const int PIN_CLK = 7; // CLK pin connection to the display
const int PIN_DIO = 6; // DIO pin connection to the display

//~ Display Constants

const int BRIGHTNESS = 3; // Display brightness (0 - 7)

//~ Game Constants

const int COUNTDOWN_SECS = 5;

const int STATE_NONE = 0;
const int STATE_WAITING = 1;
const int STATE_TICKING = 2;
const int STATE_WINNER = 3;

//~ Runtime Variables

int GameState = STATE_NONE;
unsigned long CountdownStart = 0;
int DisplayNumber = 0;
int TeamNumber = 0;
int WinnerPosition = 0;

TM1637Display display(PIN_CLK, PIN_DIO);  //set up the 4-Digit Display.





#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();
  delay(10);

  // Set display brightness
  display.setBrightness(BRIGHTNESS, true);

  display.showNumberDec(0);
}


ChipRegistry registry(10);

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
    mfrc522.PICC_HaltA();
    uint8_t value = 0;
    registry.put(mfrc522.uid.uidByte, &value);
    Serial.print("Chip number [");
    void* uid = mfrc522.uid.uidByte;
    Serial.print(*((int32_t *) uid), HEX);
    Serial.print("]: ");
    Serial.println(registry.indexOf(mfrc522.uid.uidByte));
	}
  display.showNumberDec(millis() / 1000L);
}
