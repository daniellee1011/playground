#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    condition_variable cv;
    mutex queue_mtx;
    bool stop;
public:
    ThreadPool(int numThreads) : stop(false) {
        for (int i = 0; i < numThreads; i++) {
            workers.emplace_back([this]() {
                while(true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_mtx);
                        cv.wait(lock, [this](){ return stop || !tasks.empty(); });
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
        unique_lock<mutex> lock(queue_mtx);
        tasks.push(task);
        cv.notify_one();
    }
    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for (thread& worker: workers) worker.join();
    }
};

void sampleTask(int taskId) {
    cout << "Tasks " << taskId << "is handling" << endl;
}

int main() {
    ThreadPool pool(3);

    for (int i = 1; i <= 5; i++) pool.enqueue([i](){sampleTask(i);});
    return 0;
}