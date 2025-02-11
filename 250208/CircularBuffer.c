#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 5

typedef struct {
    char buffer[BUFFER_SIZE];
    int head;
    int tail;
    bool is_full;
} CircularBuffer;

void initialize(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->is_full = false;
}

void write(CircularBuffer* cb, char data) {
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;

    if (cb->is_full) {
        cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    }

    cb->is_full = cb->head == cb->tail;
}

bool read(CircularBuffer* cb, char *data) {
    if (cb->head == cb->tail && !cb->is_full) return false;
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->is_full = false;
    return true;
}

int main() {
    CircularBuffer cb;
    initialize(&cb);

    write(&cb, 'a');
    write(&cb, 'b');
    write(&cb, 'c');

    char data;
    if (read(&cb, &data)) {
        printf("Read: %c\n", data);
    } else {
        printf("Read fails\n");
    }
    
    return 0;
}