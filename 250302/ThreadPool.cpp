#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <thread>
#include <queue>

using namespace std;

class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mtx;
    condition_variable cv;
    atomic<bool> stop;
public:
    explicit ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; i++) {
            workers.emplace_back([this]() {
                while(true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mtx);
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
            unique_lock<mutex> lock(queue_mtx);
            tasks.push(move(task));
            cout << "The size of queue: " << tasks.size() << endl;
        }
        cv.notify_one();
    }
    // Destructor to stop all threads
    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for (thread &worker : workers) {
            worker.join();
        }
    }
};

mutex print_mtx;
// Sample task function
void sampleTask(int taskId) {
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "Task " << taskId << " is executing\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ThreadPool pool(3);
    for (int i = 1; i <= 10; i++) {
        pool.enqueue([i]() { sampleTask(i); });
    }
    this_thread::sleep_for(chrono::seconds(3));
    return 0;
}