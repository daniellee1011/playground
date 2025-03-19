#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <atomic>

using namespace std;

class ThreadPool {
private:
    vector<thread> workers; // Worker threads
    queue<function<void()>> tasks; // Tasks queue
    condition_variable cv; // Task availability notification
    atomic<bool> stop; // Stop flag
    mutex queue_mutex; // Synchronization for tasks queue
public:
    ThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; i++) {
            workers.emplace_back([this]() {
                while(true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mutex);
                        cv.wait(lock, [this]() { return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) return;

                        task = tasks.front();
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    void enqueue(function<void()> task) {
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.push(move(task));
        }
        cv.notify_one();
    }
    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for (thread &worker : workers) {
            worker.join();
        }
    }
};

mutex print_mutex;
void sampleTask(int taskId) {
    {
        lock_guard<mutex> lock(print_mutex);
        cout << "Task " << taskId << " is handling\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ThreadPool pool(3);

    for (int i = 1; i <= 5; i++) {
        pool.enqueue([i]() { sampleTask(i); });
    }

    this_thread::sleep_for(chrono::seconds(3));

    return 0;
}