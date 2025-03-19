#include <iostream>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <thread>

#define MAXIMUM_BUFFER_SIZE 5

using namespace std;

class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    atomic<bool> stop;
    mutex queue_mtx;
    condition_variable cv;
public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; i++) {
            workers.emplace_back([this]() {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mtx);
                        cv.wait(lock, [this](){ return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) return;

                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    void enqueue(function<void()> task) {
        unique_lock<mutex> lock(queue_mtx);
        tasks.push(task);
        cv.notify_one();
    }
    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for (thread &worker : workers) worker.join();
    }
};

mutex print_mtx;
void sampleTask(int taskId) {
    unique_lock<mutex> lock(print_mtx);
    cout << "Task ID: " << taskId << " is processing\n";
}

int main() {
    ThreadPool pool(3);

    for (int i = 1; i <= 5; i++) {
        pool.enqueue([i]() { sampleTask(i);});
    }

    this_thread::sleep_for(chrono::seconds(3));

    cout << "Terminated gracefully\n";

    return 0;
}