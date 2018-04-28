#include <SD.h>
#include "TMRpcm.h"

TMRpcm tmrpcm;

char* FILENAME = "mac.wav";

int play() {
    tmrpcm.speakerPin = 9;
    tmrpcm.setVolume(4);
    tmrpcm.play(FILENAME);

    /*
    int res = tmrpcm.wavInfo(FILENAME);
    if (res == 0) {
        Serial.println("Error reading WAV header");
        return 0;
    }
    */
}

void setup() {
  Serial.begin(9600);
  Serial.print("Reading file: ");
  Serial.println(FILENAME);
  if (!SD.begin(4)) {
      Serial.println("Couldn't open SD");
      return;
  }
  if (!play()) {
      return;
  }
  Serial.println("Playing");
  return;
}

void loop() {
}
