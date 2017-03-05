void probe() {
  Serial.println("Probing...");
  for (int i = 2; i <= 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  bool found = false;
  for (int i = 2; i <= 12 && !found; i++) {
    for (int j = i+1; j <= 12 && !found; j++) {
      pinMode(j, INPUT);
      digitalWrite(i, HIGH);
      if (digitalRead(j) == HIGH) {
         found = true;
         Serial.println(i);
         Serial.println(j);
         Serial.println();
      }
      digitalWrite(i, LOW);
      pinMode(j, OUTPUT);
    }
  }
}
