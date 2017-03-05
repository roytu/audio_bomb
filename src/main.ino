#include "defines.h"
#include "music.h"

// Extra buttons
const int CLEAR = 10;

const int KEYS = 10;
int keys[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, CLEAR};
int probe_ins[] = {7, 5, 5, 5, 5, 6, 6, 6, 6, 7};
int probe_outs[] = {10, 11, 10, 9, 8, 11, 10, 9, 8, 11, 9};

int getKeyPress() {
  for (int i = 4; i <= 11; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for (int i = 0; i < KEYS; i++) {
    pinMode(probe_outs[i], OUTPUT);
    pinMode(probe_ins[i], INPUT);
    digitalWrite(probe_outs[i], HIGH);
    if (digitalRead(probe_ins[i]) == HIGH) {
      digitalWrite(probe_outs[i], LOW);
      pinMode(probe_ins[i], OUTPUT);
      return keys[i];
    }
    digitalWrite(probe_outs[i], LOW);
    pinMode(probe_ins[i], OUTPUT);
  }
  return -1;
}

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.begin(9600);
  playSong(1);
}

void loop() {
  int key = getKeyPress();
  if (key >= 0) {
    Serial.println("Playing song:");
    Serial.println(key);
    playSong(key);
  }
}
