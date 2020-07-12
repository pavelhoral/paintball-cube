#ifndef AUDIOOUTPUT_HPP
#define AUDIOOUTPUT_HPP

#include <Arduino.h>

const uint8_t BUZZER_PIN = 3;

const uint8_t PLAYER_TX_PIN = 0;

const uint8_t PLAYER_RX_PIN = 1;

class AudioOutput {
public:
  AudioOutput();

  /**
   * Initialize audio player.
   */
  void setup(Stream &stream);

  /**
   * Play blocking buzzer sound.
   */
  void buzz(int length, uint8_t count = 1, int pause = 50);

  /**
   * Reset any internal and physical state.
   */
  void reset();

  /**
   * Update player status.
   */
  void update();

  /**
   * Play audio file.
   */
  void play(uint8_t folder, uint8_t file, uint8_t volume = 30);

  /**
   * Stop any audio file.
   */
  void stop();

};

#endif
