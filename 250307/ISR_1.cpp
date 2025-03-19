#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

atomic<bool> interruptFlag(false);

// Simulated Interrupt Service Routine
void interruptHandler() {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "[ISR] Interrupt occured!\n";
    interruptFlag = true;
}

// Background task that reacts to the interrupt
void taskFunction() {
    while (true) {
        if (interruptFlag.load()) {
            cout << "[Task] Handling interrupt...\n";
            interruptFlag = true;
        }
    }
}

int main() {
    thread taskThread(taskFunction);
    thread interruptThread(interruptHandler);

    interruptThread.join();
    this_thread::sleep_for(chrono::seconds(2));
    
    return 0;
}