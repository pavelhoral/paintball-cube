#include <Arduino.h>
#include <TM1637Display.h>
#include <MFRC522.h>
#include <EEPROM.h>

#include "ChipRegistry.hpp"

#include "MelodyNotes.h"
#include "MelodyPlayer.hpp"

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

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

#define BUZZER_PIN 3

#define PIR_PIN 2

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool detected = false;

const int tempo = 1000;
int song[] = {
  NOTE_C3, NOTE_2(tempo),
  NOTE_E3, NOTE_2(tempo),
  NOTE_G3, NOTE_2(tempo),
  NOTE_00, NOTE_2(tempo),
  NOTE_C3, NOTE_2(tempo),
  NOTE_E3, NOTE_2(tempo),
  NOTE_G3, NOTE_2(tempo),
  NOTE_00, NOTE_2(tempo),

  NOTE_E3, NOTE_4(tempo),
  NOTE_E3, NOTE_4(tempo),
  NOTE_D3, NOTE_4(tempo),
  NOTE_E3, NOTE_4(tempo),
  NOTE_F3, NOTE_2(tempo),
  NOTE_D3, NOTE_2(tempo),

  NOTE_E3, NOTE_4(tempo),
  NOTE_E3, NOTE_4(tempo),
  NOTE_D3, NOTE_4(tempo),
  NOTE_E3, NOTE_4(tempo),
  NOTE_F3, NOTE_2(tempo),
  NOTE_D3, NOTE_2(tempo),

  NOTE_E3, NOTE_2(tempo),
  NOTE_D3, NOTE_2(tempo),
  NOTE_C3, NOTE_2(tempo)
};

MelodyPlayer melody(BUZZER_PIN);

uint8_t buttonPins[] = {A0, A1, A2};
bool buttonState[] = {false, false, false};
uint8_t buttonDebounce[] = {0, 0, 0};

void printDetail(uint8_t type, int value);

DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial swSerial(10, 11);


void setup() {
  Serial.begin(9600);
  /*
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
  */

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }


  /*
  swSerial.begin(9600);
  if (!myDFPlayer.begin(swSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  /**/
}

ChipRegistry registry(10);

void loop() {
  /*
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
  */
  unsigned long time = millis();
  melody.update(time);
  for (int i = 0; i < 3; i++) {
    bool pushed = digitalRead(buttonPins[i]) == LOW;
    bool state = buttonState[i];
    if (pushed != state) {
      if (buttonDebounce[i]++ > 20) {
        buttonState[i] = pushed;
        buttonDebounce[i] = 0;
        if (pushed) {
          Serial.print("Pressed ");
          Serial.println(i);
          melody.load(song, sizeof(song) / sizeof(int) / 2);
          melody.play();
          /*
          myDFPlayer.volume(30);  //Set volume value. From 0 to 30
          myDFPlayer.play(i + 1);  //Play the first mp3
          /**/
        }
      }
    } else if (buttonDebounce[i] != 0) {
      buttonDebounce[i] = 0;
    }
  }

  /*
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  /**/
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
