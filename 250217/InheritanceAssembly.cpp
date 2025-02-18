#include <iostream>

class GPU {
public:
    virtual void display() { std::cout << "Base GPU\n"; }
};

class Adreno : public GPU {
public:
    void display() override() { std::cout << "Adreno GPU\n"; }
};

int main() {
    GPU *gpu = new Adreno();
    gpu->display();
    delete gpu;
    return 0;
}

// vtable for Adreno:
//  .word Adreno::display

// Adreno::display:
//  push {lr}
//  ldr r0, =.LC0       // Load "Adreno GPU\n" string
//  bl printf
//  pop {lr}
//  bx lr

// main:
//  push {lr}
//  bl operator new     // Allocate memory
//  ldr r1, =vtable for Adreno
//  str r1, [r0]        // Set vtable pointer
//  bl Adreno::display
//  bl operator delete  // Free memory
//  pop {lr}
//  bx lr
