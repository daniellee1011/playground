#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>

using namespace std;

class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mtx;
    condition_variable cv;
    bool stop;
public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; i++) {
            workers.emplace_back([this]() {
                while(true) {
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
        tasks.push(move(task));
        cv.notify_one();
    }
    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for (auto &worker : workers) worker.join();
    }
};

mutex print_mtx;
void sampleTask(int taskId) {
    unique_lock<mutex> lock(print_mtx);
    cout << "Task " << taskId << " is processing" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ThreadPool pool(3);

    for (int i = 0; i < 10; i++) {
        pool.enqueue([i]() {sampleTask(i);} );
    }

    this_thread::sleep_for(chrono::seconds(3));
    
    return 0;
}