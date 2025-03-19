#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <atomic>
#include <thread>

#define MAX_BUFFER_SIZE 5

using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv_producer, cv_consumer;
atomic<bool> stop = false;

void producer() {
    int item = 0;
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_producer.wait(lock, [](){ return buffer.size() < MAX_BUFFER_SIZE; });
        item++;
        buffer.push(item);
        cout << "Produced: " << item << endl;
        cv_consumer.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_consumer.wait(lock, [](){ return !buffer.empty(); });
        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;
        cv_producer.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    this_thread::sleep_for(chrono::seconds(3));
    stop = true;

    cv_consumer.notify_all();
    cv_producer.notify_all();

    producerThread.join();
    consumerThread.join();

    return 0;
}