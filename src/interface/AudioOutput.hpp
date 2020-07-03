#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

const uint8_t BUZZER_PIN = 3;

const uint8_t PLAYER_TX_PIN = 0;

const uint8_t PLAYER_RX_PIN = 1;

class AudioOutput : public DFRobotDFPlayerMini {
public:
  AudioOutput();

  /**
   * Initialize audio player.
   */
  void setup();

  /**
   * Reset any internal and physical state.
   */
  void reset();
};

#endif
