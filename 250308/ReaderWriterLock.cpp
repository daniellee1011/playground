#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

using namespace std;

class ReaderWriterLock {
private:
    mutex mtx;
    condition_variable cv_readers, cv_writers;
    int reader_count;
    bool writer_active;
public:
    ReaderWriterLock() : reader_count(0), writer_active(false) {}
    void ReadLock() {
        unique_lock<mutex> lock(mtx);
        cv_readers.wait(lock, [this](){ return !writer_active; });
        reader_count++;
    }
    void ReadUnlock() {
        unique_lock<mutex> lock(mtx);
        reader_count--;
        if (reader_count == 0) cv_writers.notify_one();
    }
    void WriteLock() {
        unique_lock<mutex> lock(mtx);
        cv_writers.wait(lock, [this](){ return reader_count == 0 && !writer_active; });
        writer_active = true;
    }
    void WriteUnlock() {
        unique_lock<mutex> lock(mtx);
        writer_active = false;
        cv_readers.notify_all();
        cv_writers.notify_one();
    }
};

ReaderWriterLock rwLock;
int shared_data = 0;
mutex print_mtx;

void Reader(int id) {
    rwLock.ReadLock();
    {   
        unique_lock<mutex> lock(print_mtx);
        cout << "Thread " << id << " is reading: " << shared_data << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
    rwLock.ReadUnlock();
}

void Writer(int id) {
    rwLock.WriteLock();
    shared_data++;
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Thread " << id << " is writing: " << shared_data << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(200));
    rwLock.WriteUnlock();
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) threads.emplace_back(Writer, i);
        else threads.emplace_back(Reader, i);
    }

    for (auto &th : threads) th.join();
    
    return 0;
}