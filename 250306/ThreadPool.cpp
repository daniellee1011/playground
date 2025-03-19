#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

using namespace std;

class ThreadPool {
private:
    vector<thread> workers; // Worker threads
    queue<function<void()>> tasks; // Tasks queue
    mutex queue_mutex; // Synchronization for task queue
    condition_variable cv; // Task availability notification
    atomic<bool> stop; // Stop flag
public:
    explicit ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; i++) {
            workers.emplace_back([this]() {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mutex);
                        cv.wait(lock, [this]() { return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) return;

                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    // Add task to the queue
    void enqueue(function<void()> task) {
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.push(move(task));
        }
        cv.notify_one();
    }
    // Destructor to stop all threads
    ~ThreadPool() {
        stop = true;
        cv.notify_all(); // Wake up all threads
        for (thread &worker : workers) {
            worker.join();
        }
    }
};

mutex print_mtx;
// Sample tasks function
void sampleTask(int taskId) {
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "Task " << taskId << " is executing\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ThreadPool pool(3); // Create a thread pool with 3 threads

    for (int i = 1; i <= 10; i++) {
        pool.enqueue([i]() { sampleTask(i); });
    }

    this_thread::sleep_for(chrono::seconds(3));
    return 0;
}