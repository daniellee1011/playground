#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

using namespace std;

atomic<bool> interruptFlag(false);

void interruptHandler() {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "[ISR] Interrupt occured!" << endl;
    interruptFlag = true;
}

void taskFunction() {
    while (true) {
        if (interruptFlag.load()) {
            cout << "[Task] Hadling interrupt .." << endl;
            interruptFlag = true;
        }
    }
}

int main() {
    thread taskThread(taskFunction);
    thread interruptThread(interruptHandler);

    interruptThread.join();
    this_thread::sleep_for(chrono::seconds(3));

    return 0;
}