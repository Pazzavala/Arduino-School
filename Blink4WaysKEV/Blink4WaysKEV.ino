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
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 // pinMode(4, OUTPUT); //method 1

  //DDRD = DDRD | 0x10;  //method 2, set the data direction for pin 4

  asm volatile(         //method 3, legacy IO
      "sbi 0x0A,4\n\t"
      : : :
  );
  
}

// the loop function runs over and over again forever
void loop() {



  //turn light on
  //digitalWrite(4, HIGH);   // method 1
  //PORTD = PORTD | 0x10;    //method 2
  asm volatile(         //method 4, memory mapped  IO
      "lds r16, 0x002B \n\t"
      "ori r16,0x10 \n\t"
      "sts 0x002B, r16 \n\t"
      : 
      : 
      : "r16" //clobber list
  );

  
  
  delay(500);       
  

  //turn light off
  // wait for a second
 // digitalWrite(4, LOW);    // method 1
 // PORTD = PORTD & 0xEF;   //method 2
  asm volatile(         //method 3, legacy IO
      "cbi 0x0B,4\n\t"
      : : :
  );
  
  delay(500);                       // wait for a second
}
