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
        is_full = head == tail;
    }

    bool read(int &data) {
        if (head == tail && !is_full) return false;
        
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
        if (head == tail && !is_full) {
            std::cout << "Buffer is empty" << std::endl;
            return;
        }
        std::cout << "Buffer: ";
        int i = tail;
        do {
            std::cout << buffer[i] << " -> ";
            i = (i + 1) % buffer.size();
        } while (i != head);
        std::cout << "NULL" << std::endl;
    }
};

int main() {
    CircularBuffer cb(5);

    cb.write(1);
    cb.write(2);
    cb.write(3);

    int data;
    cb.read(data);
    std::cout << "Read: " << data << std::endl;

    cb.write(4);
    cb.write(5);
    cb.write(6);

    cb.print();

    cb.clear();
    cb.print();

    return 0;
}