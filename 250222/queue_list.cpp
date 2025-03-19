#include <iostream>
#include <list>

using namespace std;

class Queue {
private:
    // queue
    list<int> queue;
    // capacity
    int capacity;
public:
    // constructor
    Queue(int capacity) : capacity(capacity) {}
    // destructor
    // push
    void push(int data) {
        if (capacity == queue.size()) {
            cerr << "Queue is full" << endl;
            return;
        }
        queue.push_back(data);
    }
    // pop
    void pop() {
        if (empty()) {
            cerr << "Queue is empty" << endl;
            return;
        }
        queue.pop_front();
    }
    // front
    int front() {
        if (empty()) {
            cerr << "Queue is empty" << endl;
            return -1;
        }
        return queue.front();
    }
    // back
    int back() {
        if (empty()) {
            cerr << "Queue is empty" << endl;
            return -1;
        }
        return queue.back();
    }
    // empty
    bool empty() {
        return queue.empty();
    }
    // print
    void print() {
        for (auto &node : queue) {
            cout << node << " ";
        }
        cout << "NULL\n";
    }
};

int main() {
    Queue q(5);

    q.pop();

    q.push(1);
    q.push(2);
    q.push(3);
    q.print();

    int f = q.front();
    int b = q.back();
    cout << "f, b: " << f << ", " << b << endl;
    
    q.pop();
    q.print();

    q.push(4);
    q.push(5);
    q.push(6);
    q.print();

    q.push(7);
    q.print();

    list<int> list_;

    return 0;
}