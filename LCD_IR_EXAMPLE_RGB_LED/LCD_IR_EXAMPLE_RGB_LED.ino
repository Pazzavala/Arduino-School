//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 */

// include the library code:

#include <LiquidCrystal.h>
#include "IRremote.h"

int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects for the IR)-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

char myActionFigure[8]{
  0x0C,
  0x0C,
  0X04,
  0X1F,
  0X04,
  0X04,
  0X0A,
  0X12
};

int col = 0; //position of custom figure
int row = 0;

#define BLUE 3
#define GREEN 5
#define RED 6

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
  lcd.createChar(0, myActionFigure);
  
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  
  irrecv.enableIRIn(); // Start the receiver

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// define variables
int redValue = 0;
int greenValue = 0;
int blueValue = 0;


void loop() {
  char ch;

  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.println(results.value, HEX);
    ch = translateIRtoChar(results.value);
   
    Serial.println(ch);
    if (ch == '>'){
      col = col + 1;
    }
    if (ch == '1'){
      redValue += 5;
      if (redValue > 255){
        redValue = 255;
      }
    }
      
    Serial.println(col);
    Serial.println(row);
   
    lcd.clear();
    irrecv.resume(); // receive the next value
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, greenValue);
  } 
  lcd.setCursor(col, row);
  lcd.write((char) 0);
 
}

char translateIRtoChar(int value) // takes action based on IR code received
{
  char answer;
  switch(value)
  {
  case 0xFFA25D: answer = 'P'; break;
  case 0xFFE21D: answer = 'F'; /*("FUNC/STOP")*/; break;
  case 0xFF629D: answer = '+';/*("VOL+");*/ break;
  case 0xFF22DD: answer = '<'; /*("FAST BACK");*/    break;
  case 0xFF02FD: answer = 'p'; break;//("PAUSE");    break;
  case 0xFFC23D: answer = '>'; break;//("FAST FORWARD");   break;
  case 0xFFE01F: answer = 'd'; break;//("DOWN");    break;
  case 0xFFA857: answer = '-'; break;//("VOL-");    break;
  case 0xFF906F: answer = 'u'; break;//("UP");    break;
  case 0xFF9867: answer = '='; break;//("EQ");    break;
  case 0xFFB04F: answer = 'r'; break;//("ST/REPT");    break;
  case 0xFF6897: answer = '0'; break;//("0");    break;
  case 0xFF30CF: answer = '1'; break;//("1");    break;
  case 0xFF18E7: answer = '2'; break;//("2");    break;
  case 0xFF7A85: answer = '3'; break;//("3");    break;
  case 0xFF10EF: answer = '4'; break;//("4");    break;
  case 0xFF38C7: answer = '5'; break;//("5");    break;
  case 0xFF5AA5: answer = '6'; break;//("6");    break;
  case 0xFF42BD: answer = '7'; break;//("7");    break;
  case 0xFF4AB5: answer = '8'; break;//("8");    break;
  case 0xFF52AD: answer = '9'; break;//("9");    break;
  case 0xFFFFFFFF: answer = 'R'; break;//(" REPEAT");break;  

  default: 
    answer = 'p'; break;//(" other button : ");
  //  Serial.println(results.value);

  }// End Case
  
  delay(100); // Do not get immediate repeat

  return answer;
} 
