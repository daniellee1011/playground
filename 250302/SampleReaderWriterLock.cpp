#include <iostream>
#include <mutex>
#include <functional>
#include <thread>

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
            writer_mutex.lock(); // First reader blocks writers
        }

        lock.unlock();
        readFn(); // Critical section for readers

        lock.lock();
        reader_count--;
        if (reader_count == 0) {
            writer_mutex.unlock();
        }
    }

    void WriterLock(const function<void()>& writeFn) {
        writer_mutex.lock();
        writeFn();
        writer_mutex.unlock();
    }
};

ReaderWriterLock rwLock;
mutex print_mutex;

void ReadTask() {
    rwLock.ReadLock([]() {
        lock_guard<mutex> lock(print_mutex);
        cout << "Reading data ..." << endl;
    });
}

void WriteTask() {
    rwLock.WriterLock([]() {
        lock_guard<mutex> lock(print_mutex);
        cout << "Writing data ..." << endl;
    });
}

int main() {
    thread reader1(ReadTask);
    thread reader2(ReadTask);
    thread writer(WriteTask);

    reader1.join();
    reader2.join();
    writer.join();

    return 0;
}
