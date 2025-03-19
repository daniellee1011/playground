#include <iostream>
#include <condition_variable>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class Semaphore {
private:
    mutex mtx;
    condition_variable cv;
    atomic<int> count;
public:
    explicit Semaphore(int initial_count) : count(initial_count) {}
    // Wait (P operation)
    void wait() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; }); // Block until count > 0
        count--; // Consume one permit
    }
    // Signal (V operation)
    void signal() {
        unique_lock<mutex> lock(mtx);
        count++; // Release one permit
        cv.notify_one(); // Wake up one waiting thread
    }
};

Semaphore sem(3);
mutex print_mtx;

void worker(int id) {
    sem.wait();
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "Thread " << id << " is working" << endl;
    }
    this_thread::sleep_for(chrono::seconds(1));
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "Thread " << id << " finished" << endl;
    }
    sem.signal();
}

int main() {
    vector<thread> threads;

    // Launch multiple threads
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(worker, i);
    }

    for (auto &th : threads) th.join();

    return 0;
}