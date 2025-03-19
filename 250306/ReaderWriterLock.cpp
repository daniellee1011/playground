#include <iostream>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>

using namespace std;

class ReaderWriterLock {
private:
    int reader_count;
    mutex reader_mutex;
    mutex writer_mutex;
public:
    ReaderWriterLock() : reader_count(0) {}
    void ReadLock(const function<void()> readFn) {
        unique_lock<mutex> lock(reader_mutex);
        
        reader_count++;
        if (reader_count == 1) {
            writer_mutex.lock();
        }
        
        lock.unlock();
        readFn();

        lock.lock();
        reader_count--;
        if (reader_count == 0) {
            writer_mutex.unlock();
        }
    }
    void WriteLock(const function<void()> writeFn) {
        writer_mutex.lock();
        writeFn();
        writer_mutex.unlock();
    }
};

ReaderWriterLock rwLock;
mutex print_mutex;

void ReadTask(int id) {
    rwLock.ReadLock([id]() {
        lock_guard<mutex> lock(print_mutex);
        cout << "Reader " << id << " is reading\n";
    });
}

void WriteTask(int id) {
    rwLock.WriteLock([id]() {
        lock_guard<mutex> lock(print_mutex);
        cout << "Writer " << id << " is writing\n";
    });
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 5; i++) {
        threads.emplace_back(thread(ReadTask, i));
    }
    
    for (int i = 0; i < 3; i++) {
        threads.push_back(thread(WriteTask, i));
    }

    for (auto &t : threads) {
        t.join();
    }

    return 0;
}