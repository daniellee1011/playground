#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
} DoublyLinkedList;

void insert_at_head(DoublyLinkedList *list, int data);
void insert_at_tail(DoublyLinkedList *list, int data);
void delete_node(DoublyLinkedList *list, int data);
void print_list_forward(DoublyLinkedList *list);
void print_list_backward(DoublyLinkedList *list);

int main() {
    DoublyLinkedList list = {NULL, NULL};

    insert_at_head(&list, 10);
    insert_at_head(&list, 20);
    insert_at_tail(&list, 30);
    insert_at_tail(&list, 40);

    printf("List (Forward): ");
    print_list_forward(&list);

    printf("List (Backward): ");
    print_list_backward(&list);

    delete_node(&list, 20);
    printf("After Deleting 20 (Forward): ");
    print_list_forward(&list);

    return 0;
}

void insert_at_head(DoublyLinkedList *list, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    new_node->prev = NULL;

    if (list->head != NULL) {
        list->head->prev = new_node;
    }  else {
        // If the list is empty, set tail to the new node
        list->tail = new_node;
    }

    list->head = new_node;
}

void insert_at_tail(DoublyLinkedList *list, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->prev = list->tail;
    new_node->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
}

void delete_node(DoublyLinkedList *list, int data) {
    Node *temp = list->head;

    while (temp != NULL && temp->data != data) {
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        list->head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        list->tail = temp->prev;
    }

    free(temp);
}

void print_list_forward(DoublyLinkedList *list) {
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void print_list_backward(DoublyLinkedList *list) {
    Node *temp = list->tail;
    while (temp != NULL) {
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}