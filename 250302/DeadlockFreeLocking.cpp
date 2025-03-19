#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

class HierarchicalMutex {
private:
    mutex mtx;
    int level;
    static thread_local int prevLevel;
    int prevStoredLevel;
public:
    explicit HierarchicalMutex(int lvl) : level(lvl) {}
    void lock() {
        if (prevLevel >= level) {
            throw logic_error("Locking order violated! (Attempted to lock level " 
                + to_string(level) + " after locking level " + to_string(prevLevel) + ")");
        }
        mtx.lock();
        prevStoredLevel = prevLevel;
        prevLevel = level;
    }
    void unlock() {
        prevLevel = prevStoredLevel;
        mtx.unlock();
    }
};

thread_local int HierarchicalMutex::prevLevel = 10000;
HierarchicalMutex hiMtxA(1), hiMtxB(2);

void safeTask2(int id) {
    hiMtxA.lock();
    cout << "Thread " << id << " locked A" << endl;

    hiMtxB.lock();
    cout << "Thread " << id << " locked B" << endl;

    hiMtxB.unlock();
    hiMtxA.unlock();
}

mutex mtxA, mtxB;
mutex print_mtx;

void task(int id) {
    if (id == 1) {
        lock(mtxA, mtxB); // Lock both without risk of deadlock
        lock_guard<mutex> lockA(mtxA, adopt_lock);
        lock_guard<mutex> lockB(mtxB, adopt_lock);
    } else {
        lock(mtxA, mtxB);
        lock_guard<mutex> lockA(mtxA, adopt_lock);
        lock_guard<mutex> lockB(mtxB, adopt_lock);
    }
    lock_guard<mutex> lock(print_mtx);
    cout << "Thread " << id << " acquired both locks safely" << endl;
}

void safeTask(int id) {
    while (true) {
        unique_lock<mutex> lockA(mtxA, defer_lock);
        unique_lock<mutex> lockB(mtxB, defer_lock);
        if (try_lock(lockA, lockB)) { // Attempt to lock both, but release all if it fails
            lock_guard<mutex> lock(print_mtx);
            cout << "Thread " << id << " acquired both locks safely\n";
            return;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    thread t1(task, 1);
    thread t2(task, 2);

    t1.join();
    t2.join();

    thread t3(safeTask, 3);
    thread t4(safeTask, 4);

    t3.join();
    t4.join();

    thread t5(safeTask2, 5);
    thread t6(safeTask2, 6);
    t5.join();
    t6.join();

    return 0;
}