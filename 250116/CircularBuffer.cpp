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

    void push(int data) {
        buffer[head] = data;
        head = (head + 1) % buffer.size();

        if (is_full) {
            tail = (tail + 1) % buffer.size();
        }

        is_full = (head == tail);
    }

    int pop() {
        if (head == tail && !is_full) {
            std::cerr << "Buffer is empty!" << std::endl;
            return -1;
        }
        int data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;
        return data;
    }

    bool is_full_api() {
        return is_full;
    }

    bool is_empty_api() {
        return (head == tail) && !is_full;
    }
};

int main() {
    CircularBuffer cb(5);

    cb.push(1);
    cb.push(2);
    cb.push(3);

    std::cout << cb.pop() << std::endl;
    std::cout << cb.pop() << std::endl;

    cb.push(4);
    cb.push(5);
    cb.push(6);
    cb.push(7);
    cb.push(8);

    std::cout << cb.pop() << std::endl;
    std::cout << cb.pop() << std::endl;

    std::cout << "is_full: " << cb.is_full_api() << std::endl;
    std::cout << "is_empty: " << cb.is_empty_api() << std::endl;

    return 0;
}