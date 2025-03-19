#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

template <typename T>
class CircularBuffer {
private:
    vector<T> buffer;
    int head;
    int tail;
    bool is_full;

    mutable mutex mtx;
    condition_variable cv_not_empty;
    condition_variable cv_not_full;
public:
    CircularBuffer(int size) : buffer(size), head(0), tail(0), is_full(false) {
        if (size <= 0) throw invalid_argument("Buffer size must be greater than zero");
    }
    void write(T data) {
        unique_lock<mutex> lock(mtx);
        cv_not_full.wait(lock, [this] { return !is_full; });

        buffer[head] = data;
        head = (head + 1) % buffer.size();
        if (is_full) tail = (tail + 1) % buffer.size();
        is_full = (head == tail);

        lock.unlock();
        cv_not_empty.notify_one();
    }
    bool read(T &data) {
        unique_lock<mutex> lock(mtx);
        cv_not_empty.wait(lock, [this] { return (head != tail) || is_full; });

        if ((head == tail) && !is_full) {
            cerr << "Buffer is empty" << endl;
            return false;
        }
        data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;

        lock.unlock();
        cv_not_full.notify_one();

        return true;
    }
    void clear() {
        lock_guard<mutex> lock(mtx);
        head = tail = 0;
        is_full = false;
    }
    void print() {
        lock_guard<mutex> lock(mtx);
        int size = is_full ? buffer.size() : (head - tail + buffer.size()) % buffer.size();
        int index = tail;
        for (int i = 0; i < size; i++) {
            cout << buffer[index] << " ";
            index = (index + 1) % buffer.size();
        }
        cout << "NULL\n";
    }
    void resize(int size) {
        if (size <= buffer.size()) return;

        vector<T> new_buffer(size);

        for (int i = 0; i < buffer.size(); i++) {
            new_buffer[i] = buffer[(tail + i) % buffer.size()];
        }
        buffer = move(new_buffer);
        head = size;
        tail = 0;
        is_full = false;
    }
};

void producer(CircularBuffer<int> &cb, int start, int count) {
    for (int i = start; i < start + count; i++) {
        cb.write(i);
        cout << "Produced: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(CircularBuffer<int> &cb, int num_reads) {
    for (int i = 0; i < num_reads; i++) {
        int data;
        cb.read(data);
        if (data) cout << "Consumed: " << data << endl;
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    CircularBuffer<int> cb(5);

    thread producer1(producer, ref(cb), 1, 10);
    thread consumer1(consumer, ref(cb), 10);

    producer1.join();
    consumer1.join();

    cb.print();

    // cb.print();
    // cb.write(1);
    // cb.write(2);
    // cb.write(3);
    // cb.print();
    // int data;
    // if (cb.read(data)) {
    //     cout << "Read: " << data << endl;
    // } else {
    //     cout << "Read fails" << endl;
    // }
    // cb.print();
    // cb.write(4);
    // cb.write(5);
    // cb.write(6);
    // cb.print();
    // cb.write(7);
    // cb.write(8);
    // cb.print();
    // cb.clear();
    // cb.print();
    return 0;
}