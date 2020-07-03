#include "AudioOutput.hpp"

#define MAX_VOLUME 30

AudioOutput::AudioOutput() : DFRobotDFPlayerMini() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
}

void AudioOutput::setup() {
  begin(Serial);
  //volume(MAX_VOLUME);
}

void AudioOutput::reset() {
  digitalWrite(BUZZER_PIN, HIGH);
}
