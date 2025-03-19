#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv;
const int MAX_BUFFER_SIZE = 5;

void producer() {
    int count = 0;
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        count++;
        buffer.push(count);
        cout << "Produced: " << count << endl;

        lock.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        lock.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}