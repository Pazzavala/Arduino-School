/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink


   Methods  |    Bytes    | Percent
  ----------------------------------
   Method 1  |  924 bytes  |   2%
   Method 2  |  640 bytes  |   1%
   Method 3  |  640 bytes  |   1%
   Method 4  |  664 bytes  |   2%

*/

// the setup function runs once when you press reset or power the board
void setup() {
  /* 4 Methods to Set the data direction for pin 4 */
//  pinMode(4, OUTPUT);   // Method 1 - Arduino Functions
  
  DDRD = DDRD | 0X10;   // Method 2

//  asm volatile(         // Method 3 - Legacy I/O
//    "SBI 0x0A, 4 \n\t"
//    :
//    :
//    :
//  );

//  asm volatile (        // Method 4 - Memory Mapped I/O
//    "LDS r16, 0x002A \n\t"
//    "ORI r16, 0x10 \n\t"
//    "STS 0x002A, r16"
//    :
//    :
//    : "r16" // Clobber list
//  );
}

// the loop function runs over and over again forever
void loop() {

 /* 4 Methods to turn the LED on (HIGH is the voltage level): */ 
// digitalWrite(4, HIGH);   // Method 1 - Arduino Functions

 PORTD = PORTD | 0x10;    // Method 2

// asm volatile(            // Method 3 - Legacy I/O
//    "SBI 0x0B, 4 \n\t"
//    :
//    :
//    :
//  );

// asm volatile (           // Method 4 - Memory Mapped I/O
//  "LDS r16, 0x002B \n\t"
//  "ORI r16, 0x10 \n\t"
//  "STS 0x002B, r16 \n\t"
//  :
//  :
//  : "r16"
//  );
 
  delay(1000);
  // wait for a second


  /* 4 Methods to turn the LED off by making the voltage LOW: */
//  digitalWrite(4, LOW);     // Method 1 - Arduino Functions
  
  PORTD = PORTD & 0xEF;     // Method 2

//  asm volatile(             // Method 3 - Legacy I/O
//    "CBI 0x0B, 4 \n\t"
//    :
//    :
//    :
//  );

//  asm volatile (            // Method 4 - Memory Mapped I/O
//  "LDS r16, 0x002B \n\t"
//  "ANDI r16, 0xEF \n\t"
//  "STS 0x002B, r16 \n\t"
//  :
//  :
//  : "r16"
//  );
  delay(1000);                       // wait for a second
  
}
