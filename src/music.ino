#include "defines.h"
#include "TimerOne.h"

// SPEAK TO ME / BREATHE
int melody1[] = { G3, A3, B3, C4, D4, E4, F4, G4, -1 };
int beats1[]  = { 16, 16, 16, 16, 16, 16, 16, 16, -1 };

long tempo = 10000;
int pause = 1000;
int rest_count = 100;

volatile bool speaker = true;

// Global state
int* melody; int* beats;

// Melody state
volatile bool melody_is_playing = false;
volatile int melody_i = 0;
volatile long melody_elapsed_time = 0;
volatile int melody_timer = 0;
volatile long melody_tone_duration = 0;

void melodyNextNote() {
  noInterrupts();
  melody_i += 1;
  int tone_;
  int beat;
  long duration;
  double freq = melody[melody_i];
  if (freq == -1) {
    melody_is_playing = false;
    return;
  } else if (freq == 0) {
    tone_ = 0;
  } else {
    tone_ = int((double)(1000000.0)/freq);
  }
  beat = beats[melody_i];
  duration = beat * tempo;

  interrupts();
  melody_elapsed_time = 0;
  melody_tone_duration = duration;
  if (tone_ > 0) {
    melody_timer = tone_ / 2;
    Timer1.initialize(melody_timer);
    Timer1.attachInterrupt(toggleMelodySpeaker);
  } else {
    Timer1.attachInterrupt(melodyNextNote, duration * 100);  // 100?
  }
}

void toggleMelodySpeaker() {
  noInterrupts();
  speaker ^= 1;
  digitalWrite(SPEAKER_PIN, speaker);
  //delayMicroseconds(pause);  // Pause between notes

  melody_elapsed_time += melody_timer;
  if (melody_elapsed_time > melody_tone_duration) {
    Timer1.detachInterrupt();
    melodyNextNote();
  }
  interrupts();
}

void playSong(int song) {
  // Plays given song (0 - 9)
  if (melody_is_playing)
    return;
  switch (song) {
    case 1:
      melody = melody1;
      beats = beats1;
    break;
  }

  melody_i = -1;
  melody_is_playing = true;
  melodyNextNote();

  while(melody_is_playing) {
    delayMicroseconds(1);
  }
}
