#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

class AtomicMutex {
private:
    atomic<bool> locked = {false}; // Atomic flag
public:
    void lock() {
        while (locked.exchange(true, memory_order_acquire)) {
            // Spin (busy-wait) until the lock is acquired
        }
    }
    void unlock() {
        locked.store(false, memory_order_release);
    }
};

AtomicMutex atomicMutex;
int shared_data = 0;

// Worker function (critical section)
void worker(int id) {
    atomicMutex.lock();
    cout << "Thread " << id << " is modifying shared_data" << endl;
    shared_data++;
    this_thread::sleep_for(chrono::milliseconds(100));
    atomicMutex.unlock();
}

int main() {
    vector<thread> threads;

    // Launch 5 threads
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(worker, i);
    }

    // Wait for all threads to finish
    for (auto &th : threads) {
        th.join();
    }

    cout << "Final value of shared_data: " << shared_data << endl;
    
    return 0;
}