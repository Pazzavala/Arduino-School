//www.elegoo.com
//2016.12.9

#include "IRremote.h"

int receiver = 3; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button : ");
    Serial.println(results.value);

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.println(results.value, HEX);
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */


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
  
  delay(500); // Do not get immediate repeat

  return answer;
} 
