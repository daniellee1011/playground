#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

atomic<int> counter = 0;

void increment() {
    for (int i = 0; i < 100; i++) {
        counter++;
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Final counter value: " << counter << endl;
    return 0;
}