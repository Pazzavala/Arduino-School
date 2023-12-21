/*
 * recursive fun
 * 
 * finish sum1toN in avr assembly using recursion
 * 
 * 
 */


#include <EEPROM.h>

int __attribute__ ((noinline)) fact(int n);
int __attribute__ ((noinline)) sum1toN(int n);
int __attribute__ ((noinline)) myPower(int a, int n);




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("entering setup");
  int a,n;
  
  do{
    do{
      a = Serial.parseInt();
    }while(a==0);
    
    do{
      n = Serial.parseInt();
    }while(n==0);
  
    
    Serial.print("fact(" );
    Serial.print(a );
    Serial.print(") = " );
    Serial.println(fact(a));
  
    Serial.print("sum1toN(" );
    Serial.print(a );
    Serial.print(") = " );
    Serial.println(sum1toN(a));
  
    Serial.print("myPower(" );
    Serial.print(a );
    Serial.print(", " );
    Serial.print(n );
    Serial.print(") = " );
    Serial.println(myPower(a ,n ));
  
  }while(a < 20);
 
}

void loop() {
  // put your main code here, to run repeatedly:

}


int __attribute__ ((noinline)) fact(int n)
{
      int answer;
//      if (n== 0 || n == 1)
//        answer = 1;
//      else 
//        answer = n * fact(n-1);



    asm volatile( 
     "movw r24, %A1 \n\t" //this is the driver for our function
     "rcall rfact%= \n\t"
     "movw %A0, r24 \n\t"
     "rjmp done%= \n\t"

    "rfact%=: push r16 \n\t" //r16, r17 will be my local n
    "push r17 \n\t"
    "push r18 \n\t"
    "push r19 \n\t"
    "mov r16, r24\n\t"   //just moved n to r16, 17
    "mov r17, r25\n\t" //should be 0;
    "cpi r16, 0 \n\t"
    
    "breq baseC%= \n\t"
    
    "dec r24 \n\t" //by luck, r24 has n, now has n-1
    "rcall rfact%= \n\t"
    "movw r18, r24 \n\t" //answer from fact(n-1) i 18, 19
    "mul r18, r16 \n\t"
    "movw r24, r0\n\t"
    "mul r19, r16 \n\t"
    "add r25, r0 \n\t"
    "clr r1 \n\t" //be a good citizen, clean up after yourself
    
    "rjmp over%= \n\t"
    
    "baseC%=: ldi r24, 1 \n\t"
    
    "ldi r25,0 \n\t"
    "over%=:pop r19 \n\t"
    "pop r18 \n\t"
    "pop r17 \n\t"
    "pop r16 \n\t"
    "ret \n\t"

    "done%=: nop\n\t"
    
    : "=d" (answer)   //output list
    :"r" (n)//input list
    :    //clobber list
  );

  return answer;
}

int __attribute__ ((noinline)) sum1toN(int n)
{
    int answer;

//    if (n == 1){
//      answer = 1;
//    }else{
//      answer = n + sum1toN(n-1);
//    }
//    return answer;
  asm volatile (
    // Function Driver
    "movw r24, %A1 \n\t"
    "rcall rSum%= \n\t"
    "movw %A0, r24 \n\t"
    "rjmp done%= \n\t"
    
    // Push Function Local Variables
    "rSum%=: push r16 \n\t"
    "push r17 \n\t"
    "push r18 \n\t"
    "push r19 \n\t"
  
    // Move function parameter variable "n" into Local Variable
    "movw r16, r24 \n\t"
    // Comparison
    "cpi r16, 1 \n\t"
    // Branch & Else Statement
    "breq baseC%= \n\t"
    // Decrement our n
    "dec r24 \n\t"
    // Recursive call on n-1
    "rcall rSum%= \n\t"
    // Move answer from n-1 to r18,19
    "movw r18, r24 \n\t"
    "add r18, r16 \n\t"
    "adc r19, r17 \n\t"
    "movw r24, r18 \n\t" 
    // Relative Jump over Then
    "rjmp over%= \n\t"
    // Branch Then Statement & Base Case
    "baseC%=: ldi r24, 1 \n\t"
    "ldi r25, 0 \n\t"
    // jump to Over & Pop off the stack
    "over%=: pop r19 \n\t"
    "pop r18 \n\t"
    "pop r17 \n\t"
    "pop r16 \n\t"
    //return Statement
    "ret \n\t"

    "done%=: nop \n\t"
    
    : "=d" (answer)
    : "r" (n)
    :
  );
  return answer;
}


int __attribute__ ((noinline)) myPower(int a, int n)
{
    int answer;

//    if (n == 0){
//      answer = 1;
//    }else{
//      answer = a * myPower(a, n-1);
//    }

    asm volatile( 
     "movw r24, %A1 \n\t" //this is the driver for our function, load a as a parameter
     "movw r22, %A2 \n\t" //load n into 22, 23
     "rcall rPow%= \n\t"
     "movw %A0, r24 \n\t"
     "rjmp done%= \n\t"  

//*********************** actual function
    "rPow%=: push r16 \n\t" //  r16, r17 will be my local a
    "push r17 \n\t"
    "push r18 \n\t"       //  local r18, 19 local n
    "push r19 \n\t"       //  local temp var
    "push r20 \n\t"
    "push r21 \n\t"     
    "movw r16, r24\n\t"   //  just moved a to r16, r17
    "movw r18, r22\n\t"   //  just moved n to r18, r19
    "cpi r18, 0 \n\t"
    "cpc r19, r1 \n\t"    //  make sure the high byte is zero
    "breq baseC%= \n\t"

    "subi r22, 1 \n\t"    //  n still in r22,23
    "sbci r23, 0 \n\t"
    "rcall rPow%= \n\t"
    "mul r24, r16 \n\t"
    "movw r20, r0\n\t"
    "mul r25, r16 \n\t"
    "add r21, r0 \n\t"
    "mul r24, r17 \n\t"
    "add r21, r0 \n\t"
    "movw r24, r20\n\t"   //  leave the answer in the usual spot
    "clr r1 \n\t"         //  be a good citizen, clean up after yourself
    "rjmp over%= \n\t"
   
    "baseC%=: ldi r24, 1 \n\t"
    "ldi r25,0 \n\t"
    "over%=:pop r21 \n\t"
    "pop r20 \n\t"
    "pop r19 \n\t"
    "pop r18 \n\t"
    "pop r17 \n\t"
    "pop r16 \n\t"
    "ret \n\t"
//************************** end of function

    "done%=: nop\n\t"
    
    : "=d" (answer)   //  output list
    :"r" (a), "r" (n) //  input list
    :    //   clobber list
  );

  return answer;
}
