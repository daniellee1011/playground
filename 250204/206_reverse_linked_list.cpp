#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* _reverseList(ListNode* head) {
        if (!head) return head;
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    ListNode* reverseList(ListNode* head) {
        return helper(nullptr, head);
    }

    ListNode* helper(ListNode* prev, ListNode* curr) {
        if (!curr) return prev;
        ListNode* next = curr->next;
        curr->next = prev;
        return helper(curr, next);
    }
};