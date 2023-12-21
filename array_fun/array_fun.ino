void asmFillPointerArray(int A[], int n);
void asmFillPointerArray25(int A[], int n);
void asmReverseStackArray(int A[], int n);
void asmBubbleSort(int A[], int n);
void fillArrayPowersOf2(int A[], int n);

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  int n = 10;
  int a[n];
  
  Serial.println("Fill by 10's assembly code:");
  asmFillPointerArray(a, n);
  printArray(a,n);
  
  Serial.println("Fill by 25's assembly code:");
  asmFillPointerArray25(a, n);
  printArray(a,n);
  
  Serial.println("Reverse array assembly code:");
  asmReverseStackArray(a, n);
  printArray(a, n);

  Serial.println("fill by powers of 2:");
  asmFillArrayPowersOf2(a, n);
  printArray(a, n);
  
  Serial.println("Fill array with randome numbers:");
  fillArrayRandom(a, n);
  printArray(a, n);

  Serial.println("Sort array with randome numbers:");
  asmBubbleSort(a, n);
  printArray(a, n);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printArray(int A[], int n) {
  int i;

  for(i = 0; i< n; i++) {
    Serial.print(A[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  
  for(i = 0; i < n; ++i)
  {
    int addr = &A[i]; 

    Serial.print(addr,HEX); 
    Serial.print(" ");
  }
   Serial.println(" \n");
}

void asmFillPointerArray(int A[], int n) {
  
  asm volatile(

    "movw r30, %A0 \n\t" // Low byte: Moving address into z, points to start of array
    "ldi r16, 0 \n\t"    // Load i with 0
    "ldi r18, 10 \n\t"   // Low byte: Load fill with 10
    "ldi r19, 0 \n\t"    // High byte: Load fill with 0
    "ldi r20, 10 \n\t"  // Counting by 10s
    "ldi r21, 0 \n\t"
    
    // for loop
    "top%=: cp r16, %A1 \n\t" // Start of for loop
    "brge done%= \n\t"
    "st z+, r18 \n\t"    // Store the low byte
    "st z+, r19 \n\t"
    "add r18, r20 \n\t"
    "adc r19, r21 \n\t"
    "inc r16 \n\t"
    "rjmp top%= \n\t" // Moves back to top of loop
    "done%=: nop \n\t"
    
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r20","r21","r30", "r31"
  );
}

void asmFillPointerArray25(int A[], int n) {

  asm volatile(
    "movw r30, %A0 \n\t"  // Low byte: z
    "ldi r16, 0 \n\t"     // i
    "ldi r18, 25 \n\t"    // fill
    "ldi r19, 0 \n\t"
    "ldi r20, 25 \n\t"
    "ldi r21, 0 \n\t"
    
    "top%=: cp r16, %A1 \n\t"   // Strat for loop
    "brge done%= \n\t"          // Comparison
    "st z+, r18 \n\t"
    "st z+, r19 \n\t"
    "add r18, r20 \n\t"
    "adc r19, r21 \n\t"
    "inc r16 \n\t"              // i++
    "rjmp top%= \n\t"           // for loop
    "done%=: nop \n\t"
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r20","r21","r30", "r31"
  );
}

void asmReverseStackArray(int A[], int n) {

  asm volatile(
    // Push on stack
    "movw r30, %A0 \n\t"    // z points to begining of Array
    "ldi r16, 0 \n\t"
    
    "for%=: cp r16, %A1 \n\t"
    "brge done%= \n\t"
    "ld r18, z+ \n\t"
    "ld r19, z+ \n\t"
    "push r18 \n\t"
    "push r19 \n\t"
    "inc r16 \n\t"
    "rjmp for%= \n\t"
    "done%=: nop \n\t"

    // Pop off the stack
    "movw r30, %A0 \n\t"
    "ldi r16, 0 \n\t"
    
    "forr%=: cp r16, %A1 \n\t"
    "brge donee%= \n\t"
    "pop r19 \n\t"    // Pop takes high byte first
    "pop r18 \n\t"    // Then the low byte
    "st z+, r18 \n\t" 
    "st z+, r19 \n\t"
    "inc r16 \n\t"
    "rjmp forr%= \n\t"
    "donee%=: nop\n\t"
    
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r26","r27","r30", "r31"
   );
  
}

void asmFillArrayPowersOf2(int A[], int n) {

  asm volatile(
    "movw r30, %A0 \n\t"
    "ldi r16, 0 \n\t"
    "ldi r18, 1 \n\t"
    "ldi r19, 0 \n\t"

    "top%=: cp r16, %A1 \n\t"
    "brge done%= \n\t"
    "lsl r18 \n\t"
    "rol r19 \n\t"
    "st z+, r18 \n\t"
    "st z+, r19 \n\t"

    "inc r16 \n\t"
    "rjmp top%= \n\t"
    "done%=: nop \n\t"

    :
    : "d" (A), "d" (n)
    : "r16", "r18", "r19", "r20", "r21", "r30", "r31"
  );
}

void fillArrayRandom(int A[], int n)
{
  int i;
  for(i = 0; i < n; ++i)
  {
    A[i] = random(1, 100);
  }
}

void asmBubbleSort(int A[], int n) {
  asm volatile(
    "movw r30, %A0 \n\t"  // Low byte: z holds &A[0]
    "ldi r22, 0 \n\t"     // Set i to 1

    "outter%=: cp r22, %A1 \n\t"  //  Start of Outter for loop comparing i
    "brge done1%= \n\t"           
    "ldi r16, 0 \n\t"             // Set j to 1 for the inner loops, repeat n-1 times
    "movw r30, %A0 \n\t"
    "inner%=: cp r16, %A1 \n\t"     // Strat of inner for loop comparing j
    "brge done%= \n\t"          // Comparison
    
    "ld r18, z \n\t"            // load A[j]
    "ldd r19, z+1 \n\t"         
    "ldd r20, z+2 \n\t"         // load A[j+1]
    "ldd r21, z+3 \n\t"

    "cp r20, r18 \n\t"
    "cpc r21, r19 \n\t"
    "brge over%= \n\t"
    
    // Swap
    "st z, r20 \n\t"      
    "std z+1, r21 \n\t"
    "std z+2, r18 \n\t"   
    "std z+3, r19 \n\t"
    
    "over%=: adiw z, 2 \n\t"
    "inc r16 \n\t"          // i++
    "rjmp inner%= \n\t"     // for loop
    "done%=: adiw z, 2 \n\t"
    "inc r22 \n\t"
    "rjmp outter%= \n\t"
    "done1%=: nop \n\t"
    
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r20","r21","r22","r23","r30", "r31"
  );
  
}
