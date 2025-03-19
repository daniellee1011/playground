#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <queue>

#define MAXIMUM_BUFFER_SIZE 5

using namespace std;

mutex mtx;
condition_variable cv_producer, cv_consumer;
atomic<bool> stop = false;
queue<int> buffer;

void producer() {
    int item = 0;
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_producer.wait(lock, []() { return buffer.size() < MAXIMUM_BUFFER_SIZE; });
        
        item++;
        buffer.push(item);

        cout << "Produced: " << item << endl;
        cv_consumer.notify_one();
    }
}

void consumer() {
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_consumer.wait(lock, []() { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();

        cout << "Consumed: " << item << endl;
        cv_producer.notify_one();
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

    cout << "Gracefully terminated" << endl;

    return 0;
}