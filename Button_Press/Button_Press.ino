void setup() {
  // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  static char lightOn = 0;
  if (digitalRead(2) == HIGH) {
    lightOn = !lightOn;
    if (lightOn)
      digitalWrite(3, HIGH);
    else
       digitalWrite(3, LOW);
    delay(200);
  }

}
