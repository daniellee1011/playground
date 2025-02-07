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
        if (head == tail && !is_full) return false;
        data = buffer[tail];
        tail = (tail + 1) % buffer.size();
        is_full = false;
        return true;
    }

    size_t size() const {
        if (is_full) {
            return buffer.size();
        }
        return (head - tail + buffer.size()) % buffer.size();
    }

    void clear() {
        head = tail = 0;
        is_full = false;
    }
};

int main() {
    CircularBuffer cb(5);
    int data = -1;

    cb.write(1);
    cb.write(2);
    cb.write(3);

    cb.read(data);
    std::cout << "Read: " << data << std::endl;
    std::cout << "Size: " << cb.size() << std::endl;

    cb.write(4);
    cb.write(5);
    cb.write(6);

    cb.read(data);
    std::cout << "Read: " << data << std::endl;
    std::cout << "Size: " << cb.size() << std::endl;

    cb.clear();
    std::cout << "Size: " << cb.size() << std::endl;

    return 0;
}