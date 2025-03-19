#include <iostream>

class ListNode {
public:
    int data;
    ListNode* next;

    ListNode(int x) : data(x), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
public:
    LinkedList() : head(nullptr) {}

    void insert(int data) {
        ListNode* newNode = new ListNode(data);

        // if (!head) {
        //     head = newNode;
        //     return;
        // }

        newNode->next = head;
        head = newNode;
    }

    bool remove(int data) {
        if (!head) {
            std::cout << "Linked List is empty" << std::endl;
            return false;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;

        if (head->data == data) {
            head = head->next;
            delete curr;
            return true;
        }

        while (curr && curr->data != data) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) {
            std::cout << "Data is not in the LinkedList" << std::endl;
            return false;
        }

        prev->next = curr->next;
        delete curr;

        return true;
    }

    void print() {
        if (!head) {
            std::cout << "Linked List is empty" << std::endl;
            return;
        }
        ListNode *temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } std::cout << "NULL" << std::endl;
    }

    ~LinkedList() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList ll;

    ll.insert(1);
    ll.insert(2);
    ll.insert(3);
    ll.print();

    ll.remove(2);
    ll.print();

    ll.insert(4);
    ll.insert(5);
    ll.insert(6);
    ll.print();

    return 0;
}