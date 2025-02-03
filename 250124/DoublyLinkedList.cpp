#include <iostream>

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode* prev;

    ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    ListNode* head;
    ListNode* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insert(int value) {
        ListNode* newNode = new ListNode(value);

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void remove(int value) {
        ListNode* temp = head;
        while (temp && temp->val != value) {
            temp = temp->next;
        }

        if (!temp) return;

        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;

        if (temp == head) head = temp->next;
        if (temp == tail) tail = temp->prev;

        delete temp;
    }

    void printFoward() {
        ListNode* temp = head;
        while (temp) {
            std::cout << temp->val << " <-> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    void printBackward() {
        ListNode* temp = tail;
        while (temp) {
            std::cout << temp->val << " <-> ";
            temp = temp->prev;
        }
        std::cout << "NULL" << std::endl;
    }

    ~DoublyLinkedList() {
        ListNode* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.printFoward();
    list.printBackward();

    list.remove(2);
    list.printFoward();

    return 0;
}