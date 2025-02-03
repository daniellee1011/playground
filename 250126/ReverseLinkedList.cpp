#include <iostream>
#include <string>

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

    bool remove(int data) {
        if (!head) return false;
        if (head->data == data) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        ListNode *prev = nullptr;
        ListNode* curr = head;

        while (curr && curr->data != data) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) return false;
            
        if (prev) {
                prev->next = curr->next;
        }
        delete curr;

        return true;
    }

void reverseList() {
    if (!head) {
        return;
    }

    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* next = curr->next;

        curr->next = prev;
        prev = curr;
        curr = next;  // Crashing here? Check next's value in logs.
    }

    head = prev;  // Update the head safely
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

    std::string s = ll.remove(3) ? "True" : "False";
    std::cout << s << std::endl;
    ll.print();

    ll.reverseList();
    ll.print();

    return 0;
}