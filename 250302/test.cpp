#include <iostream>
#include <thread>
#include <mutex>
#include <stdexcept>
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

thread_local int HierarchicalMutex::prevLevel = 0; // ✅ Corrected Initial Value

HierarchicalMutex hiMtxA(1), hiMtxB(2);

// ✅ Correct Locking Order (A → B)
void safeTaskCorrect(int id) {
    try {
        cout << "Thread " << id << " attempting to lock A" << endl;
        hiMtxA.lock();
        cout << "Thread " << id << " locked A" << endl;

        cout << "Thread " << id << " attempting to lock B" << endl;
        hiMtxB.lock();
        cout << "Thread " << id << " locked B" << endl;

        hiMtxB.unlock();
        cout << "Thread " << id << " unlocked B" << endl;

        hiMtxA.unlock();
        cout << "Thread " << id << " unlocked A" << endl;
    } catch (const logic_error& e) {
        cout << "Thread " << id << " ERROR: " << e.what() << endl;
        hiMtxA.unlock(); // Ensure unlocking
        hiMtxB.unlock(); // Ensure unlocking
    }
}

// ❌ Incorrect Locking Order (B → A) (Should trigger exception)
void safeTaskIncorrect(int id) {
    try {
        cout << "Thread " << id << " attempting to lock B" << endl;
        hiMtxB.lock();
        cout << "Thread " << id << " locked B (Wrong Order!)" << endl;

        cout << "Thread " << id << " attempting to lock A" << endl;
        hiMtxA.lock();
        cout << "Thread " << id << " locked A (Wrong Order!)" << endl;

        hiMtxA.unlock();
        hiMtxB.unlock();
    } catch (const logic_error& e) {
        cout << "Thread " << id << " ERROR: " << e.what() << endl;
    }
}

int main() {
    thread t1(safeTaskCorrect, 1);  // ✅ Correct Order (A → B)
    thread t2(safeTaskIncorrect, 2); // ❌ Incorrect Order (B → A) (should fail)

    t1.join();
    // t2.join();

    return 0;
}
