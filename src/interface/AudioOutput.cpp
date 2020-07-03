#include <DFRobotDFPlayerMini.h>

#include "AudioOutput.hpp"

#define DEFAULT_VOLUME 30

DFRobotDFPlayerMini player;

AudioOutput::AudioOutput() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
}

void AudioOutput::setup(Stream &stream) {
  if (!player.begin(stream)) {
    buzz(5, 5, 70);
  }
  player.volume(DEFAULT_VOLUME);
}

void AudioOutput::reset() {
  digitalWrite(BUZZER_PIN, HIGH);
  player.stop();
}

void AudioOutput::buzz(int length, uint8_t count, int pause) {
  for (uint8_t i = 0; i < count; i++) {
    if (i > 0) {
      delay(pause);
    }
    digitalWrite(BUZZER_PIN, LOW);
    delay(length);
    digitalWrite(BUZZER_PIN, HIGH);
  }
}

void AudioOutput::update() {
  if (player.available()) {
    player.readType();
    player.read();
  }
}

void AudioOutput::play(uint8_t folder, uint8_t file) {
  player.playFolder(folder, file);
}
