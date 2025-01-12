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

    void write(int value) {
        buffer[head] = value;
        head = (head + 1) % buffer.size();

        if (is_full) {
            tail = (tail + 1) % buffer.size();
        }

        is_full = (head == tail);
    }

    int read() {
        if (head == tail && !is_full) {
            std::cerr << "Buffer is empty!\n";
            return -1;
        }

        int value = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;

        return value;
    }
};

int main() {
    CircularBuffer cb(5);

    cb.write(1);
    cb.write(2);
    cb.write(3);

    std::cout << "Read: " << cb.read() << "\n";
    std::cout << "Read: " << cb.read() << "\n";

    cb.write(4);
    cb.write(5);
    cb.write(6);

    std::cout << "Read: " << cb.read() << "\n";
    std::cout << "Read: " << cb.read() << "\n";
    std::cout << "Read: " << cb.read() << "\n";

    return 0;
}