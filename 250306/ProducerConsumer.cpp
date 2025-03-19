#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv_producer, cv_consumer;
const int MAX_BUFFER_SIZE = 5;
bool stop = false;

void producer() {
    int item = 0;

    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_producer.wait(lock, []() { return buffer.size() < MAX_BUFFER_SIZE; });

        if (stop) break;

        buffer.push(++item);
        cout << "Produced: " << item << endl;

        cv_consumer.notify_one();
        this_thread::sleep_for(chrono::microseconds(500));
    }
}

void consumer() {
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_consumer.wait(lock, []() { return !buffer.empty() || stop; });

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        cv_producer.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    vector<thread> producers;
    vector<thread> consumers;

    for (int i = 0; i < 5; i++) producers.emplace_back(producer);
    for (int i = 0; i < 3; i++) consumers.emplace_back(consumer);

    // thread producerThread(producer);
    // thread consumerThread(consumer);

    this_thread::sleep_for(chrono::seconds(5));  // Let them run for a while
    stop = true;  // Set stop flag

    cv_producer.notify_all();
    cv_consumer.notify_all();

    for (auto &p : producers) p.join();
    for (auto &c : consumers) c.join();

    // producerThread.join();
    // consumerThread.join();

    cout << "Producer-Consumer terminated gracefully." << endl;

    return 0;
}