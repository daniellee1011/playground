#include <iostream>
#include <list>

using namespace std;
    
class Stack {
private:
    int capacity;
    list<int> stack;
public:
    Stack(int capacity) {
        this->capacity = capacity;
    }

    void push(int data) {
        if (stack.size() == capacity) {
            cerr << "Stack is full" << endl;
            return;
        }
        stack.push_front(data);
    }

    void pop() {
        if (stack.size() == 0) {
            cerr << "Stack is empty" << endl;
            return;
        }
        stack.pop_front();
    }

    int top() {
        if (stack.size() == 0) {
            cerr << "Stack is empty" << endl;
            return -1;
        }
        return stack.front();
    }

    void print() {
        for (int &node : stack) {
            cout << node << " ";
        }
        cout << "\n";
    }
};

int main() {
    Stack s(5);

    s.pop();

    s.push(1);
    s.push(2);
    s.push(3);
    s.print();

    int data = s.top();
    cout << "Top: " << data << endl;
    s.pop();

    s.push(4);
    s.push(5);
    s.push(6);
    s.print();

    s.push(7);

    return 0;
}