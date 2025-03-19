#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

using namespace std;

class ReaderWriterLock {
private:
    int reader_count;
    bool writer_active;
    mutex mtx;
    condition_variable cv_read, cv_write;
public:
    void lockRead() {
        unique_lock<mutex> lock(mtx);
        cv_read.wait(lock, [this](){ return !writer_active; });
        reader_count++;
    }
    void unlockRead() {
        unique_lock<mutex> lock(mtx);
        reader_count--;
        if(reader_count == 0) cv_write.notify_one();
    }
    void lockWrite() {
        unique_lock<mutex> lock(mtx);
        cv_write.wait(lock, [this](){ return reader_count == 0 && !writer_active; });
        writer_active = true;
    }
    void unlockWrite() {
        unique_lock<mutex> lock(mtx);
        writer_active = false;
        cv_write.notify_one();
        cv_read.notify_all();
    }
};

ReaderWriterLock rwLock;
int shared_data = 0;
mutex print_mtx;

void read(int id) {
    rwLock.lockRead();
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Read " << id << " is reading: " << shared_data << endl;
    }
    rwLock.unlockRead();
}

void write(int id) {
    rwLock.lockWrite();
    shared_data++;
    {
        unique_lock<mutex> lock(print_mtx);
        cout << "Write " << id << " is writing: " << shared_data << endl;
    }
    rwLock.unlockWrite();
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) threads.emplace_back(write, i);
        else threads.emplace_back(read, i);
    }

    // this_thread::sleep_for(chrono::seconds(3));

    for (auto &th : threads) th.join();

    return 0;
}