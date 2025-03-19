#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

class ReaderWriterLock {
private:
    mutex mtx;
    condition_variable cv_read, cv_write;
    int reader_count = 0; // Number of active readers
    bool writer_active = false; // Is a writer active?
public:
    // Acquire lock for reading
    void lockRead() {
        unique_lock<mutex> lock(mtx);
        cv_read.wait(lock, [this]() { return !writer_active; });
        reader_count++;
    }
    // Release lock after reading
    void unlockRead() {
        unique_lock<mutex> lock(mtx);
        reader_count--;
        if (reader_count == 0) cv_write.notify_one(); // Notify writer if no more readers
    }
    // Acquire lock for writing
    void lockWrite() {
        unique_lock<mutex> lock(mtx);
        cv_write.wait(lock, [this]() { return reader_count == 0 && !writer_active; });
        writer_active = true;
    }
    // Release lock after wrting
    void unlockWrite() {
        unique_lock<mutex> lock(mtx);
        writer_active = false;
        cv_read.notify_all(); // Allow readers
        cv_write.notify_one(); // Allow next writer
    }
};

// Shared lock instance
ReaderWriterLock rwLock;
int shared_data = 0;
mutex print_mtx;

// Reader function
void reader(int id) {
    rwLock.lockRead();
    {
        lock_guard<mutex> lock(print_mtx);
        cout << "Reader " << id << " is reading: " << shared_data << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate read time
    rwLock.unlockRead();
}

// Writer function
void writer(int id) {
    rwLock.lockWrite();
    {
        lock_guard<mutex> lock(print_mtx);
        shared_data++;
        cout << "Writer " << id << " is writing: " << shared_data << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(200)); // Simulate write time
    rwLock.unlockWrite();
}

int main() {
    vector<thread> threads;

    // Launch multiple readers and writers
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(reader, i);
        if (i % 2 == 0) threads.emplace_back(writer, i);
    }

    for (auto& th : threads) th.join();

    return 0;
}