#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>

using namespace std;

class Semaphore {
private:
    int reference_count;
    mutex mtx;
    condition_variable cv;
public:
    Semaphore(int initial_count) : reference_count(initial_count) {}
    void wait() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this](){ return reference_count > 0; });
        reference_count--;
    }
    void signal() {
        unique_lock<mutex> lock(mtx);
        reference_count++;
        cv.notify_one();
    }
};

Semaphore sem(3);
mutex print_mtx;

void worker(int id) {
    sem.wait();
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Task " << id << " is working" << endl;
    }
    this_thread::sleep_for(chrono::seconds(1));
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Task " << id << " finished" << endl;
    }
    sem.signal();
}

int main() {
    vector<thread> workers;

    for (int i = 0; i < 10; i++) {
        workers.emplace_back(worker, i);
    }

    // this_thread::sleep_for(chrono::seconds(10));
    for (auto &worker : workers) worker.join();

    return 0;
}