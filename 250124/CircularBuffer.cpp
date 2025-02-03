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

    int read() {
        if (head == tail && !is_full) {
            std::cerr << "Buffer is empty" << std::endl;
            return -1;
        }

        int data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;

        return data;
    }

    bool getFull() {
        return is_full;
    }
};

int main() {
    CircularBuffer cb(5);

    cb.write(1);
    cb.write(2);
    cb.write(3);

    std::cout << "Read: " << cb.read() << std::endl;
    std::cout << "Read: " << cb.read() << std::endl;

    cb.write(4);
    cb.write(5);
    cb.write(6);
    cb.write(7);

    std::cout << "Is Full: " << cb.getFull() << std::endl;
    std::cout << "Read: " << cb.read() << std::endl;
    std::cout << "Is Full: " << cb.getFull() << std::endl;
}