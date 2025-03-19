#include <iostream>
#include <atomic>

using namespace std;

atomic<char> letter = 'A';

void changeLetter() {
    letter.store('B', memory_order_release);
}

int main() {
    changeLetter();
    cout << "New letter: " << letter.load(memory_order_acquire) << endl;
    return 0;
}