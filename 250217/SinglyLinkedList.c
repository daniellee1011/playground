#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* insert(Node *head, int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* delete(Node *head, int data) {
    Node *prev = NULL;
    Node *curr = head;

    while (curr && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) return head;
    
    if (!prev) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }

    free(curr);
    return head;
}

void print(Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    
    head = insert(head, 1);
    head = insert(head, 2);
    head = insert(head, 3);
    print(head);

    head = delete(head, 2);
    print(head);

    head = insert(head, 4);
    head = insert(head, 5);
    head = insert(head, 6);
    print(head);

    freeList(head);

    return 0;
}
