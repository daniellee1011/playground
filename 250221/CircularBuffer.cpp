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
    CircularBuffer(size_t size) {
        buffer = vector<int>(size);
        head = 0;
        tail = 0;
        is_full = false;
    }

    void write(int data) {
        buffer[head] = data;
        head = (head + 1) % buffer.size();
        if(is_full) tail = (tail + 1) % buffer.size();
        is_full = (head == tail);
    }

    bool read(int &data) {
        if ((head == tail) && !is_full) {
            cerr << "Buffer is empty!" << endl;
            return false;;
        }
        data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;
        return true;
    }

    void clear() {
        head = 0;
        tail = 0;
        is_full = false;
    }

    void print() {
        int index = tail;
        cout << "head, tail: " << head << ", " << tail << endl;
        int size = is_full ? 5 : (head - tail + buffer.size()) % buffer.size();
        cout << "size: " << size << endl;
        for (int i = 0; i < size; i++) {
            cout << buffer[index++] << " -> ";
            index %= buffer.size();
        }
        cout << "NULL \n";
    }
};

int main() {
    CircularBuffer cb(5);

    cb.write(1);
    cb.write(2);
    cb.write(3);
    cb.print();

    int data;    
    if (cb.read(data)) {
        cout << "Read: " << data << endl;
    }

    cb.write(4);
    cb.write(5);
    cb.write(6);
    cb.print();

    cb.write(7);
    cb.write(8);
    cb.write(9);
    cb.print();

    return 0;
}