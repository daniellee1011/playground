#include <iostream>

using namespace std;

class Stack {
private:
    // * variables
    // array
    int *stack;
    // size
    int size;
    // stack pointer
    int pointer;
public:
    // * functions
    // constructor
    Stack(int size) {
        stack = new int[size];
        this->size = size;
        pointer = -1;
    }
    // push
    void push(int value) {
        if (pointer == (size - 1)) {
            cerr << "The stack is full" << endl;
            return;
        }
        stack[++pointer] = value;
    }
    // pop
    void pop() {
        if (pointer < 0) {
            cerr << "The stack is empty" << endl;
            return;
        }
        pointer--;
    }
    // top
    int top() const {
        if (pointer < 0) {
            cerr << "The stack is empty" << endl;
            return -1;
        }
        return stack[pointer];
    }
    // print
    void print() {
        if (pointer < 0) {
            cerr << "The stack is empty" << endl;
            return;
        }
        for (int i = 0; i <= pointer; i++) {
            cout << stack[i] << " ";
        }
        cout << "\n";
    }
    // destructor
    ~Stack() {
        delete[] stack;
    }
};

int main() {
    Stack s(5);

    s.push(1);
    s.push(2);
    s.push(3);
    s.print();

    int data = s.top();
    cout << "Data: " << data << endl;

    s.pop();
    s.push(4);
    s.push(5);
    s.print();

    return 0;
}