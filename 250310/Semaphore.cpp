#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore {
private:
    int reference_count;
    condition_variable cv;
    mutex mtx;
public:
    Semaphore(int initial_count) : reference_count(initial_count);
    void acquire() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this](){ return reference_count > 0; });
        reference_count--;
    }
    void release() {
        unique_lock<mutex> lock(mtx);
        reference_count++;
        cv.notify_one();
    }
};

int main() {
    return 0;
}