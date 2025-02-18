#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 5, y = 10;
    int result = add(x, y);
    printf("Result: %d\n", result);
    return 0;
}

// add:
//  adds r0, r0, r1 // r0 = r0 + r1
//  bx lr           // Return

// main:
//  push {lr}       // Save return address
//  mov r0, #5      // x = 5
//  mov r1, #10     // y = 10;
//  bl add          // Call add
//  mov r3, r0      // Store result in r3
//  bl printf       // Call printf
//  pop {lr}        // Restore return address
//  bx lr           // Return
