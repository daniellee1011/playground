#include <iostream>
#include <vector>

#define BUFFER_SIZE 5

using namespace std;

class CircularBuffer {
private:
    // vector<int> buffer;
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    bool is_full;
public:
    CircularBuffer() : head(0), tail(0), is_full(false) {}
    // CircularBuffer(int size) : buffer(size), head(0), tail(0), is_full(false) {
    //     if (size <= 0) {
    //         throw invalid_argument("Buffer size must be greater than zero.");
    //     }
    // }
    void write(int data) {
        buffer[head] = data;
        // head = (head + 1) % buffer.size();
        head = (head + 1) % BUFFER_SIZE;
        if (is_full) {
            // tail = (tail + 1) % buffer.size();
            tail = (tail + 1) % BUFFER_SIZE;
        }
        is_full = (head == tail);
    }
    int read() {
        if ((head == tail) && !is_full) {
            cerr << "Buffer is empty!" << endl;
            return -1;
        }
        int data = buffer[tail];
        // tail = (tail + 1) % buffer.size();
        tail = (tail + 1) % BUFFER_SIZE;
        is_full = false;
        return data;
    }
    void clear() {
        head = tail = 0;
        is_full = false;
    }
    void print() {
        // int size = is_full ? buffer.size() : (head - tail + buffer.size()) % buffer.size();
        int size = is_full ? BUFFER_SIZE : (head - tail + BUFFER_SIZE) % BUFFER_SIZE;
        int index = tail;
        for (int i = 0; i < size; i++) {
            cout << buffer[index] << " ";
            // index = (index + 1) % buffer.size();
            index = (index + 1) % BUFFER_SIZE;
        } cout << "NULL\n";
    }
};

int main() {
    // CircularBuffer cb(5);
    CircularBuffer cb;
    cb.print();
    cb.write(1);
    cb.write(2);
    cb.write(3);
    cb.print();
    int data = cb.read();
    if (data != -1) {
        cout << "data: " << data << endl;
    } else {
        cout << "Read fails" << endl;
    }
    cb.print();
    cb.write(4);
    cb.write(5);
    cb.write(6);
    cb.print();
    cb.write(7);
    cb.write(8);
    cb.print();
    cb.clear();
    cb.print();
    return 0;
}