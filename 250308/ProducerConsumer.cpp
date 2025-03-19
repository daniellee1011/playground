#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

#define MAX_BUFFER_SIZE 5

using namespace std;

queue<int> buffer;
mutex mtx;
condition_variable cv_prod, cv_cons;
bool stop = false;

void producer() {
    int item = 0;
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_prod.wait(lock, [](){ return buffer.size() < MAX_BUFFER_SIZE; });
        item++;
        buffer.push(item);
        cout << "Producer: " << item << endl;
        cv_cons.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    while (!stop) {
        unique_lock<mutex> lock(mtx);
        cv_cons.wait(lock, [](){ return !buffer.empty(); });
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer: " << item << endl;
        cv_prod.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread prodThread(producer);
    thread consThread(consumer);

    this_thread::sleep_for(chrono::seconds(5));

    stop = true;

    cv_prod.notify_all();
    cv_cons.notify_all();

    prodThread.join();
    consThread.join();
    
    return 0;
}