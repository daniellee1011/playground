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

        if (!head) {
            head = newNode;
        } else {
            ListNode* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void remove(int data) {
        if (!head) return;
        if (head->data == data) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->data != data) {
            prev = curr;
            curr = curr->next;
        }
        
        if (curr) {
            prev->next = curr->next;
            delete curr;
        }
    }

    void reverse() {
        // 1 -> 2 -> 3 -> 4 (head)
        // 1 <- 2 <- 3 <- 4
        if (!head) return;

        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }

    void print() {
        ListNode* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }
};

int main() {
    LinkedList ll;
    ll.insert(1);
    ll.insert(2);
    ll.insert(3);
    ll.insert(4);
    ll.insert(5);
    ll.print();

    ll.remove(3);
    ll.print();

    ll.reverse();
    ll.print();
    
    return 0;
}