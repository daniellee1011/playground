#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>

using namespace std;

class ReaderWriterLock {
private:
    int reader_count;
    bool writer_active;
    mutex mtx;
    condition_variable cv_readers, cv_writers;
public:
    ReaderWriterLock() : reader_count(0), writer_active(false) {}
    void lockRead() {
        unique_lock<mutex> lock(mtx);
        cv_readers.wait(lock, [this](){ return !writer_active; });
        reader_count++;
    }
    void unlockRead() {
        unique_lock<mutex> lock(mtx);
        reader_count--;
        if (reader_count == 0) cv_writers.notify_one();
    }
    void lockWriter() {
        unique_lock<mutex> lock(mtx);
        cv_writers.wait(lock, [this](){ return reader_count == 0 && !writer_active; });
        writer_active = true;
    }
    void unlockWriter() {
        unique_lock<mutex> lock(mtx);
        writer_active = false;
        cv_writers.notify_one();
        cv_readers.notify_all();
    }
};

ReaderWriterLock rwLock;
int shared_data = 0;
mutex print_mtx;

void reader(int id) {
    rwLock.lockRead();
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Task " << id << " is reading: " << shared_data << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    rwLock.unlockRead();
}

void writer(int id) {
    rwLock.lockWriter();
    shared_data++;
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Task " << id << " is writing: " << shared_data << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    rwLock.unlockWriter();
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 20; i++) {
        if (i % 2 == 0) threads.emplace_back(writer, i);
        else threads.emplace_back(reader, i);
    }

    for (auto &th : threads) th.join();
    
    return 0;
}