/*
  This code is to play with arithmetic and branch instructions
  Notice it uses the serial port for input and output
 */

int __attribute__ ((noinline)) addTwo(int a, int b);
int __attribute__ ((noinline)) subTwo(int a, int b);
int __attribute__ ((noinline)) multTwo(int a, int b);
int __attribute__ ((noinline)) divTwo(int a, int b);
long __attribute__ ((noinline)) multTwoLongs(long a, long b);

int __attribute__ ((noinline)) lessOrEqual(int a, int b);
int __attribute__ ((noinline)) greaterThen(int a, int b);

//these are the four to finish, please add code in setup to test each one
int __attribute__ ((noinline)) lessThen(int a, int b);
int __attribute__ ((noinline)) greaterOrEqual(int a, int b);
int __attribute__ ((noinline)) equal(int a, int b);
int __attribute__ ((noinline)) notEqual(int a, int b);

// the setup function runs once when you press reset or power the board
void __attribute__ ((noinline))setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
 Serial.begin(9600);
 
  int a = 300, b = 24, g = 0;

  do{
    //get the first number
    Serial.println("enter 2 numbers");
    while(! Serial.available()){
        ;
    }
    a = Serial.parseInt();
/*      // Entering two number seperately
    g = Serial.parseInt(); 
        //  try for a second number
    Serial.println("enter another number");
    while(! Serial.available()){
        ;
    }
*/
    b = Serial.parseInt();
    g = Serial.parseInt(); // variable collecting Garbage or the enter
    
    Serial.print(" a = ");
    Serial.println(a);
    Serial.print(" b = ");
    Serial.println(b);
    
    int answer;
    
    Serial.print(" a + b = ");
    answer = addTwo(a, b);
    Serial.println(answer);

    Serial.print(" a - b = ");
    answer = subTwo(a, b);
    Serial.println(answer);

    Serial.print(" a * b = ");
    answer = multTwo(a, b);
    Serial.println(answer);

    Serial.print(" a / b = ");
    answer = divTwo(a, b);
    Serial.println(answer);
   
    Serial.print("  a > b ");
     answer = greaterThen(a, b);
    Serial.println(answer);
   
    Serial.print(" a <= b ");
    answer = lessOrEqual(a, b);
    Serial.println(answer);

    Serial.print("  a < b ");
    answer = lessThen(a, b);
    Serial.println(answer);
    
    Serial.print(" a >= b ");
    answer = greaterOrEqual(a, b);
    Serial.println(answer);
    //add code to test the four new functions
    Serial.println();
  }while(1);
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}


int __attribute__ ((noinline)) addTwo(int a, int b)
{
  int answer;
//  answer = a + b;

  asm volatile(
    "add %A1, %A2 \n\t" //add together the low bytes
    "adc %B1, %B2 \n\t" //add together 
    "mov %A0, %A1 \n\t" //
    "mov %B0, %B1 \n\t" 
    : "=d" (answer)   //output list
    : "r" (a),"r" (b) //input list
    :    //clobber list
  );
 
  return answer;
}

int __attribute__ ((noinline)) subTwo(int a, int b)
{
    int answer;
//    answer = a - b;

    asm volatile(
      "SUB %A1, %A2 \n\t"
      "SBC %B1, %B2 \n\t"
      "MOV %A0, %A1 \n\t"
      "MOV %B0, %B1 \n\t"
      : "=d" (answer) // Output list
      : "r" (a), "r" (b) // Input list
      : // Clobber list
      );
      
    return answer;
}

int __attribute__ ((noinline)) multTwo(int a, int b)
{
  int answer;
  answer = a * b;
 
  return answer;
}
int __attribute__ ((noinline)) divTwo(int a, int b)
{
    int answer = a / b;
    return answer;
}

int __attribute__ ((noinline)) greaterThen(int a, int b)
{
  int answer;

  asm volatile(
    "cp  %A2,%A1 \n\t"  // b - a
    "cpc  %B2,%B1 \n\t"  // b - a
    "brlt then%= \n\t"  //
    "ldi  %A0, 0  \n\t" //do the over
    "rjmp over%= \n\t" //jump over the then
    "then%=: ldi %A0, 1 \n\t" //
    "over%=: ldi %B0, 0  \n\t" //done with the upper byte of answer
    : "=d" (answer)   //output list
    : "r" (a),"d" (b) //input list
    :    //clobber list
   );

  return answer;
}

int __attribute__ ((noinline)) lessOrEqual(int a, int b)
{
  int answer;
//  if (a <= b)
//    answer = 1;
//  else
//    answer = 0;
 asm volatile(
    "cp %A2, %A1 \n\t" // b-a (low byte)
    "cpc %B2, %B1 \n\t" //b-a (high byte)
    "brge then%= \n\t"  //
    "ldi %A0, 0 \n\t" //load answer with 0
    "rjmp done%= \n\t" //don't fall into the then
    "then%=: ldi %A0, 1 \n\t" //load answer with 1
    "done%=: ldi %B0, 0 \n\t"
    : "=d" (answer)   //output list
    : "r" (a),"r" (b) //input list
    :    //clobber list
  );
 

  return answer;
}

int __attribute__ ((noinline)) lessThen(int a, int b)
{
  int answer;
//  a < b

  asm volatile(
    "CP %A1, %A2 \n\t"
    "CPC %B1, %B2 \n\t"
    "BRLT then%= \n\t"
    "LDI %A0, 0 \n\t"
    "RJMP done%= \n\t"
    "then%=: LDI %A0, 1 \n\t"
    "done%=: LDI %B0, 0 \n\t"
    : "=d" (answer)
    : "r" (a), "r" (b)
    :
  );
  return answer;
}

int __attribute__ ((noinline)) greaterOrEqual(int a, int b)
{
  int answer;
//  a >= b
  asm volatile(
    "CP %A1, %A2 \n\t"
    "CPC %B1, %B2 \n\t"
    "BRGE then%= \n\t"
    "LDI %A0, 0 \n\t"
    "RJMP done%= \n\t"
    "then%=: LDI %A0, 1 \n\t"
    "done%=: LDI %B0, 0 \n\t"
    : "=d" (answer)
    : "r" (a), "r" (b)
    :
  );
  return answer;
  
}

int __attribute__ ((noinline)) equal(int a, int b)
{
  int answer = 0;
  return answer;
  
}
int __attribute__ ((noinline)) notEqual(int a, int b)
{
  int answer = 0;
  return answer;
  
}
