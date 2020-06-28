#ifndef MELODYPLAYER_H
#define MELODYPLAYER_H

#include <Arduino.h>

class MelodyPlayer {
public:
  /**
   * Create new player for the specified PIN number.
   */
  MelodyPlayer(uint8_t outputPin);

  /**
   * Load the given song.
   */
  void load(int* song, int length);

  /**
   * Start playback of the loaded song.
   */
  void play();

  /**
   * Stop the current playback.
   */
  void stop();

  /**
   * Update output based on playback status.
   */
  void update(unsigned long time);

private:
  /**
   * Buzzer output pin.
   */
  uint8_t outputPin_;

  /**
   * Playback state.
   */
  uint8_t playbackState_;

  /**
   * Current song array.
   */
  int* song_;

  /**
   * Current song length
   */
  int songLength_ = 0;

  /**
   * Current song position.
   */
  int songPosition_;

  /**
   * Time of next scheduled note change.
   */
  unsigned long nextUpdate_;
};

#endif
