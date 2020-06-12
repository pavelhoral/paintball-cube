#include <Arduino.h>
#include <TM1637Display.h>

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

void setup() {
  Serial.begin(9600);
  // Set display brightness
  display.setBrightness(BRIGHTNESS, true);
}

void loop() {
  display.showNumberDec(millis() / 1000L);
  delay(1000);
  Serial.println("Loop completed...");
}
