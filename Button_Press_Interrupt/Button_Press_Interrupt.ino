volatile char lightOn = 0;
void setup() {
  // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  attachInterrupt(digitalPinToInterrupt(2), buttonPressed, RISING);

}

void buttonPressed() {
  
  lightOn = !lightOn;
  
  if (lightOn)
    digitalWrite(3, HIGH);
  else
     digitalWrite(3, LOW);
     
}
