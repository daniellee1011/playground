#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <queue>

using namespace std;

struct Task {
    int priority;
    function<void()> func;

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

class PriorityThreadPool {
private:
    vector<thread> workers;
    priority_queue<Task> tasks;
    mutex queue_mtx;
    condition_variable cv;
    atomic<bool> stop;
public:
    PriorityThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i <= numThreads; i++) {
            workers.emplace_back([this](){
                while (true) {
                    Task task;
                    {
                        unique_lock<mutex> lock(queue_mtx);
                        cv.wait(lock, [this]() { return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) return;

                        task = tasks.top();
                        tasks.pop();
                    }
                    task.func();
                }
            });
        }
    }
    void enqueue(int priority, function<void()> func) {
        {
            unique_lock<mutex> lock(queue_mtx);
            tasks.push(Task{priority, move(func)});
        }
        cv.notify_one();
    }
    ~PriorityThreadPool() {
        stop = true;
        cv.notify_all();
        for (thread &worker : workers) {
            worker.join();
        }
    }
};

mutex print_mtx;
void sampleTask(int taskId, int priority) {
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "Task " << taskId << ": " << priority << " is executing\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    PriorityThreadPool pool(3);

    pool.enqueue(1, []() { sampleTask(1, 1); });
    pool.enqueue(3, []() { sampleTask(2, 3); });
    pool.enqueue(2, []() { sampleTask(3, 2); });
    pool.enqueue(5, []() { sampleTask(4, 5); });
    pool.enqueue(4, []() { sampleTask(5, 4); });

    this_thread::sleep_for(chrono::seconds(3));
    return 0;
}