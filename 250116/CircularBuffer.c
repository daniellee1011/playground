#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

typedef struct CircularBuffer {
    int *buffer;
    int head;
    int tail;
    int size;
    bool is_full;
} CircularBuffer;

void init_buffer(CircularBuffer *cb);
void push(CircularBuffer *cb, int data);
bool pop(CircularBuffer *cb, int *data);
bool is_full(CircularBuffer *cb);
bool is_empty(CircularBuffer *cb);
void print_buffer(CircularBuffer *cb);

int main() {
    CircularBuffer *cb;
    init_buffer(cb);

    push(cb, 1);
    push(cb, 2);
    push(cb, 3);

    int data;
    pop(cb, &data); printf("Popped: %d\n", data);
    pop(cb, &data); printf("Popped: %d\n", data);

    push(cb, 4);
    push(cb, 5);
    push(cb, 6);

    printf("is_full: %s\n", is_full(cb) ? "full" : "not full");
    printf("is_empty: %s\n", is_empty(cb) ? "empty" : "not empty");

    pop(cb, &data); printf("Popped: %d\n", data);
    pop(cb, &data); printf("Popped: %d\n", data);

    push(cb, 7);
    push(cb, 8);
    push(cb, 9);
    push(cb, 10);

    printf("is_full: %s\n", is_full(cb) ? "full" : "not full");
    printf("is_empty: %s\n", is_empty(cb) ? "empty" : "not empty");

    print_buffer(cb);

    free(cb);

    return 0;
}

void init_buffer(CircularBuffer *cb) {
    cb->buffer = (int*)malloc(sizeof(int) * BUFFER_SIZE);
    cb->head = 0;
    cb->tail = 0;
    cb->size = BUFFER_SIZE;
    cb->is_full = false;
}

void push(CircularBuffer *cb, int data) {
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % cb->size;

    if (cb->is_full) {
        cb->tail = (cb->tail + 1) % cb->size;
    }

    cb->is_full = cb->head == cb->tail;
}

bool pop(CircularBuffer *cb, int *data) {
    if (cb->head == cb->tail && !cb->is_full) {
        printf("Buffer is empty!\n");
        return false;
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % cb->size;
    cb->is_full = false;
    return true;
}

bool is_full(CircularBuffer *cb) {
    return cb->is_full;
}

bool is_empty(CircularBuffer *cb) {
    return (cb->head == cb->tail) && !cb->is_full;
}

void print_buffer(CircularBuffer *cb) {
    int index = cb->tail;
    int count = is_full(cb) ? cb->size : (cb->head - cb->tail + cb->size) % cb->size;

    for (int i = 0; i < count; i++) {
        printf("%d -> ", cb->buffer[index]);
        index = (index + 1) % cb->size;
    } printf("NULL\n");
}