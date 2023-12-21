void printArray(int A[], int n);
void fillArray(int A[], int n);
void fillPointerArray(int A[], int n);
void asmFillPointerArray(int A[], int n);
void fillArray25(int A[] ,int n);
void fillPointerArray25(int A[] ,int n);
void asmFillPointerArray25(int A[], int n);
void reverseArray(int A[], int n);
void reversePointerArray(int A[], int n);
void reverseStackArray(int A[], int n);
void fillArrayPowersOf2(int A[], int n);
void shiftFillArrayPowersOf2(int A[], int n);
void asmBubbleSort(int A[], int n);
void fillArrayRandom(int A[], int n);
void asmReverseStackArray(int A[], int n);

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  int n = 20;
  int a[20];
  
  Serial.println("Fill by 10's:");
  fillArray(a, n);
  printArray(a,n);
  
  Serial.println("Fill by 10's using pointer:");
  fillPointerArray(a, n);
  printArray(a,n);
  
  Serial.println("Fill by 10's assembly code:");
  asmFillPointerArray(a, n);
  printArray(a,n);
  
  Serial.println("Fill by 25's:");
  fillArray25(a, n);
  printArray(a, n);
  
  Serial.println("Fill by 25's using pointer:");
  fillPointerArray25(a, n);
  printArray(a, n);
  
  Serial.println("Fill by 25's assembly code:");
  asmFillPointerArray25(a, n);
  printArray(a,n);
  
  Serial.println("Reverse Array:");
  reverseArray(a, n);
  printArray(a, n);
  
  Serial.println("Reverse Pointer Array:");
  reversePointerArray(a, n);
  printArray(a, n);
  
  reverseStackArray(a, n);
  printArray(a, n);

  asmReverseStackArray(a, n);
  
  fillArrayRandom(a, n);
  printArray(a, n);
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

void fillArray(int A[], int n) {
  int i, fill;
  fill = 10;

  for(i = 0; i < n; i++) {
    A[i] = fill;
    fill += 10;
  }
}

void fillPointerArray(int A[], int n) {
  
  int i, fill;
  int *p = A;
  
  fill = 10;
 

  for(i = 0; i < n; i++) {
    *p = fill;
    p++;
    fill += 10;
  }
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

void fillArray25(int A[] ,int n) {

  int i, fill;

  fill = 25;

  for( i = 0; i < n; i++) {
    A[i] = fill;
    fill += 25;
  }
}

void fillPointerArray25(int A[] ,int n) {
  int i, fill, *p;

  p = A;
  fill = 25;
  
  for(i = 0; i < n; i++) {
    *p = fill;
    p++;
    fill += 25;
  }
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

void reverseArray(int A[], int n) {
  int i, aEnd, temp;

  aEnd = n;
  
  for(i = 0; i <= aEnd; i++) {
    temp = A[i];
    A[i] = A[--aEnd];
    A[aEnd] = temp;
  }
}

void reversePointerArray(int A[], int n) {
  int *pStart, *pEnd, temp;

  pStart = A;
  pEnd = A + n-1;

  while(pStart < pEnd) {
    temp = *pStart;
    *pStart = *pEnd;
    *pEnd = temp;

    pStart++;
    pEnd--;
  }
}

void asmReverseArray(int A[], int n) {

  asm volatile(
    // Push on stack
    "movw r30, %A0 \n\t"    // z points to begining of Array
    "ldi r16, 0 \n\t"
    
    
    "top%=: cp r16, %A1 \n\t"
    "brge done%= \n\t"
    "ld r18, z+ \n\t"
    "ld r19, z+ \n\t"
    "push r18 \n\t"
    "push r19 \n\t"
    "inc r16 \n\t"
    "rjmp top%= \n\t"
    "done%=: nop \n\t"

    // Pop off the stack
    "movw r40, %A0 \n\t"
    "ldi r16, 0 \n\t"
    
    "top%=: cp r16, %A1 \n\t"
    "brge done%= \n\t"
    "pop r19 \n\t"    // Pop takes high byte first
    "pop r18 \n\t"    // Then the low byte
    "st z+, r18 \n\t" 
    "st z+, r19 \n]t"
    "rjmp top%= \n\t"
    "done%=: nop\n\t"
    
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r30", "r31"
   );
  
}

void reverseStackArray(int A[], int n) {
  int stack[n], i, current;
  
  current = 0;
  
  // Push to Stack
  for(i = 0; i < n; i++) {
    stack[current++] = A[i];
  }

  // Pop from Stack
  for(i = 0; i < n; i++) {
    A[i] = stack[--current];
  }
  
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
    "movw r26, %A0 \n\t"
    "ldi r16, 0 \n\t"
    
    "forr%=: cp r16, %A1 \n\t"
    "brge done%= \n\t"
    "pop r19 \n\t"    // Pop takes high byte first
    "pop r18 \n\t"    // Then the low byte
    "st x+, r18 \n\t" 
    "st x+, r19 \n]t"
    "rjmp forr%= \n\t"
    "done%=: nop\n\t"
    
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r30", "r31","r26","r27"
   );
  
}

void fillArrayPowersOf2(int A[], int n) {
  int i, fill;

  fill = 1;

  for(i = 0; i < n; i++) {
    A[i] = fill;
    fill *= 2;
  }
}

void shiftFillArrayPowersOf2(int A[], int n) {
  int i, fill;

  fill = 1;

  for(i = 0; i < n; i++) {
    A[i] = fill;
    fill <<= 1;
  }
}

void asmShiftFillArrayPowersOf2(int A[], int n) {

  asm volatile(
    "ldi r16, 0"


    "top%=: cp r16, %A1 \n\t"
    "brge done%= \n\t"

    "rjmp top%= \n\t"
    "done%= nop \n\t"

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
    "ldi r16, 1 \n\t"     // Set j to 1 for the inner loops, repeat n-1 times
    "ldi r22, 1 \n\t"     // Set i to 1 for outter loop

    "outter%=: cp r22, %A1 \n\t"  //  Start of Outter for loop comparing i
    "brge done1%= \n\t"
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
    "st z, r20 \n\r"      
    "std z+1, r21 \n\t"
    "std z+2, r18 \n\t"   
    "std z+3, r19 \n\t"
    "over%=: adiw r30, 2 \n\t"
    "adiw z, 2 \n\t"
    "inc r16 \n\t"          // i++
    "rjmp inner%= \n\t"     // for loop
    "done%=: nop \n\t"
    "movw r40, %A0 \n\t"
    "adiw z, 2 \n\t"
    "inc r22 \n\t"
    "rjmp outter%= \n\t"
    "done1%=: nop \n\t"
    
    :
    : "d" (A), "d" (n)
    : "r16","r18","r19","r20","r21","r22","r23","r30", "r31"
  );
  
}

void arrayPractice(void) {
  int i, j, Data[3][4];

  for(i = 0; i < 3; i++) {
    for(j = 0; j < 4; j++) {
      Data[i][j] = i * 4 + j + 1;
      }
  }

  for(i = 0; i < 3; i++) {
    for(j = 0; j < 4; j++) {
      Serial.print(Data[i][j]);
      Serial.print(" ");
      }
      Serial.println();
  }
}
