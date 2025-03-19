#include <iostream>
#include <vector>

class CircularBuffer {
private:
    std::vector<int> buffer;
    int head;
    int tail;
    bool is_full;
public:
    CircularBuffer(size_t size) : buffer(size), head(0), tail(0), is_full(false) {}

    void write(int data) {
        buffer[head] = data;
        head = (head + 1) % buffer.size();
        if (is_full) {
            tail = (tail + 1) % buffer.size();
        }
        is_full = (head == tail);
    }

    bool read(int &data) {
        if ((head == tail) && !is_full) return false;

        data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;
        return true;
    }

    void clear() {
        std::cout << "Buffer is cleared" << std::endl;
        head = 0;
        tail = 0;
        is_full = false;
    }

    void print() {
        if ((head == tail) && !is_full) {
            std::cout << "Buffer is empty" << std::endl;
            return;
        }

        int index = tail;
        int count = is_full ? buffer.size() : (head - tail + buffer.size()) % buffer.size();
        for (int i = 0; i < count; i++) {
            std::cout << buffer[index] << " ";
            index = (index + 1) % buffer.size();
        }
        std::cout << "NULL\n";
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
        std::cout << "Read: " << data << std::endl;
    }
    cb.print();

    cb.write(4);
    cb.write(5);
    cb.write(6);
    cb.print();

    cb.clear();
    cb.print();
}