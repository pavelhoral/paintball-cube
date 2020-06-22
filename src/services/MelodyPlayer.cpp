#include "MelodyPlayer.hpp"

#include "MelodyNotes.h"

#define PLAYBACK_STOPPED 0
#define PLAYBACK_PLAYING 1

#define stopTone(outputPin) noTone(outputPin); digitalWrite(outputPin, HIGH);

MelodyPlayer_::MelodyPlayer_(uint8_t outputPin) : outputPin_(outputPin) {
}

void MelodyPlayer_::load(int* song, int length) {
  song_ = song; // Use reference only
  songLength_ = length;
  songPosition_ = 0;
  playbackState_ = PLAYBACK_STOPPED;
}

void MelodyPlayer_::play() {
  if (playbackState_ == PLAYBACK_STOPPED && songLength_ > 0) {
    playbackState_ = PLAYBACK_PLAYING;
  }
  nextUpdate_ = 0; // Force immediate update
}

void MelodyPlayer_::stop() {
  Serial.print("Stopping playback...");
  playbackState_ = PLAYBACK_STOPPED;
  stopTone(outputPin_);
}

void MelodyPlayer_::update(unsigned long time) {
  if (playbackState_ != PLAYBACK_PLAYING || nextUpdate_ > time) {
    return;
  } else if (songPosition_ >= songLength_) {
    stop();
    return;
  }
  int idx = songPosition_ * 2;
  int note = song_[idx];
  if (note == NOTE_00) {
    stopTone(outputPin_);
  } else {
    tone(outputPin_, note);
  }
  nextUpdate_ = time + song_[idx + 1];
  songPosition_++;
}
