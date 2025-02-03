#include <iostream>

class ListNode {
public:
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedList {
private:
    ListNode *head;

public:
    LinkedList() : head(nullptr) {}

    void insert(int value) {
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = newNode;
            return;
        }
        ListNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void remove(int value) {
        if (!head) return;
        if (head->val == value) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->val != value) {
            prev = curr;
            curr = curr->next;
        }

        if (curr) {
            prev->next = curr->next;
            delete curr;
        }
    }

    bool search(int value) {
        ListNode* temp = head;
        while (temp) {
            if (temp->val == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void print() {
        ListNode* temp = head;
        while (temp) {
            std::cout << temp->val << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    ~LinkedList() {
        ListNode *temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.print();

    list.remove(2);
    list.print();

    std::cout << "Search 3: " << (list.search(3) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 5: " << (list.search(5) ? "Found" : "Not Found") << std::endl;
}