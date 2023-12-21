void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);

  DDRD = DDRD & 0x10;

  asm volatile (
    "sbi 0x0A, 4 \n\t"
    :
    :
    :
  )

  asm volatile (
  "lds r16, 0x002A \n\t"
  "andi r16, 0x10 \n\t"
  "sts 0x002A, r16 \n\t"
  :
  :
  : "r16"
  )

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);

  PORTD = PORTD | 0x10;
  PORTD = PORTD & 0xEF;

  asm volatile(
    "sbi 0x0B, 4 \n\t"
    :
    :
    :
  )  

  asm volatile(
    "cbi 0x0B, 4 \n\t"
    :
    :
    :
  )  

  asm volatile(
    "lds r16, 0x002B \n\t"
    "ori r16, 0x10 \n\t"
    "sts 0x002B, r16 \n\t"
    :
    :
    : "r16"
  )

  asm volatile(
    "lds r16, 0x002B \n\t"
    "andi r16, 0x10 \n\t"
    "sts 0x002B, r16 \n\t"

   :
   :
   : "r16"
}
