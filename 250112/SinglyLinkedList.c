#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Insert a node at the head
void insert_node(Node **head, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

// Delete a node by value
void delete_node(Node **head, int data) {
    Node *temp = *head, *prev = NULL;
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    if (prev != NULL) prev->next = temp->next;
    else *head = temp->next;
    free(temp);
}

// Search for a node by value
Node *search_node(Node *head, int data) {
    while (head != NULL) {
        if (head->data == data) return head;
        head = head->next;
    }
    return NULL;
}

void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;

    insert_node(&head, 10);
    insert_node(&head, 20);
    insert_node(&head, 30);

    print_list(head);

    return 0;
}