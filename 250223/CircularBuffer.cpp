#include <iostream>
#include <vector>

using namespace std;

class CircularBuffer {
private:
    vector<int> buffer;
    int head;
    int tail;
    bool is_full;
public:
    CircularBuffer(size_t size) : buffer(size), head(0), tail(0), is_full(false) {}
    void write(int data) {
        buffer[head] = data;
        head = (head + 1) % buffer.size();
        if (is_full) tail = (tail + 1) % buffer.size();
        is_full = (head == tail);
    }
    bool read(int &data) {
        if ((head == tail) && !is_full) {
            cerr << "Buffer is empty!" << endl;
            return false;
        }
        data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;
        return true;
    }
    void clear() {
        head = tail = 0;
        is_full = false;
    }
    void print() {
        int size = is_full ? buffer.size() : (head + buffer.size() - tail) % buffer.size();
        int index = tail;
        for (int i = 0; i < size; i++) {
            cout << buffer[index] << " ";
            index = (index + 1) % buffer.size();
        } cout << "NULL\n";
    }
};

int main() {
    CircularBuffer cb(5);
    cb.print();
    cb.write(1);
    cb.write(2);
    cb.write(3);
    cb.print();
    int data;
    if (cb.read(data)) {
        cout << "Read: " << data << endl;
    } else {
        cout << "Read fails" << endl;
    }
    cb.print();
    cb.write(4);
    cb.write(5);
    cb.write(6);
    cb.print();
    return 0;
}