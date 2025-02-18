#include <stdio.h>

int setBit(int num, int pos) {
    return num | (1 << pos);
}

int main() {
    int n = 5;
    n = setBit(n, 1);
    printf("Result: %d\n", n);
    return 0;
}

// setBit:
//  mov r2, #1      // Load 1
//  lsl r2, r2, r1  // Shift left by r1
//  orr r0, r0, r2  // Or operation
//  bx lr           // Return

// main:
//  push {lr}
//  mov r0, #5      // Load 5 into r0
//  mov r1, #1      // Load 1 into r1
//  bl setBit       // Call setBit
//  bl printf       // Call printf
//  pop {lr}
//  bx lr
