#include <iostream>

using namespace std;

class Queue {
private:
    int *queue;
    int size;
    int head;
    int tail;
public:
    // constructor
    Queue (int size) : queue(new int[size * 2]), size(size), head(0), tail(-1) {}
    // destructor
    ~Queue () {
        delete[] queue;
    }
    // push
    void push (int data) {
        if (size == size_()) {
            cerr << "Queue is full" << endl;
            return;
        }
        queue[++tail] = data;
    }
    // pop
    void pop () {
        if (empty()) {
            cerr << "Queue is empty" << endl;
            return;
        }
        head++;
    }
    // front
    int front() {
        if (empty()) {
            cerr << "Queue is empty" << endl;
            return -1;
        }
        return queue[head];
    }
    // back
    int back() {
        if (empty()) {
            cerr << "Queue is empty" << endl;
            return -1;
        }
        return queue[tail];
    }
    // size
    int size_() {
        return tail - head + 1;
    }
    // empty
    bool empty() {
        return head > tail ? true : false;
    }
    // swap
    // print
    void print() {
        for (int i = head; i <= tail; i++) {
            cout << queue[i] << " ";
        }
        cout << "NULL\n";
    }
};

int main() {
    Queue q(5);

    q.print();

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

    return 0;
}