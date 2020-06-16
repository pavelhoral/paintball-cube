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

#define BUZZER_PIN 8

#define PIR_PIN 2

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool detected = false;

#include "Sound.h"

int notes[] = {
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3
};

int song[] = {
  NOTE_C3, NOTE_2,
  NOTE_E3, NOTE_2,
  NOTE_G3, NOTE_2,
  NOTE_NN, NOTE_2,
  NOTE_C3, NOTE_2,
  NOTE_E3, NOTE_2,
  NOTE_G3, NOTE_2,
  NOTE_NN, NOTE_2,
};
bool songPlay = false; 
unsigned long songStart = 0;
int songPos = 0;
int songLength = 8;


boolean play() {
  if (songPos == songLength) {
    noTone(BUZZER_PIN);
    songPos = 0;
    return false;
  }
  if (songStart == 0) {
    songStart = millis();
  }

  for (int i = 0; i < count; i++) {
    int note = song[i * 2];
    int duration = song[i * 2 + 1];
    if (note == NOTE_NN) {
      tone(BUZZER_PIN, NOTE_C1, duration);
    } else {
      tone(BUZZER_PIN, note, duration);
    }
  }
  noTone(BUZZER_PIN);
}

void setup() {
  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();
  delay(10);

  // Set display brightness
  display.setBrightness(BRIGHTNESS, true);
  display.clear();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  delay(50);
  digitalWrite(BUZZER_PIN, HIGH);

  pinMode(PIR_PIN, INPUT);
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
    int cardId = registry.indexOf(mfrc522.uid.uidByte);
    Serial.println(cardId);
    display.showNumberDec(cardId);

    if (cardId == 0) {
      play(song, 8);
    } else {
      tone(BUZZER_PIN, notes[cardId % 5], 50);
    }
    delay(50);
    digitalWrite(BUZZER_PIN, HIGH);
	}
  if (digitalRead(PIR_PIN) == HIGH) {
    uint8_t fullhouse[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
    display.setSegments(fullhouse);
    tone(BUZZER_PIN, NOTE_C1, 1);
    delay(1);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(250);
    display.clear();
  }
}
