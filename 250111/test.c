#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 5

// Define the circular buffer structure
typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    bool is_full;
} CircularBuffer;

void buffer_init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->is_full = false;
}

void buffer_write(CircularBuffer *cb, int value) {
    cb->buffer[cb->head] = value;
    cb->head = (cb->head + 1) % BUFFER_SIZE;

    if (cb->is_full) {
        cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    }

    cb->is_full = (cb->head == cb->tail);
}

int buffer_read(CircularBuffer *cb) {
    if (cb->head == cb->tail && !cb->is_full) {
        printf("Buffer is empty\n");
        return -1;
    }

    int value = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->is_full = false;

    return value;
}

int main() {
    CircularBuffer cb;
    buffer_init(&cb);

    buffer_write(&cb, 1);
    buffer_write(&cb, 2);
    buffer_write(&cb, 3);

    printf("Read: %d\n", buffer_read(&cb));
    printf("Read: %d\n", buffer_read(&cb));

    buffer_write(&cb, 4);
    buffer_write(&cb, 5);
    buffer_write(&cb, 6);

    printf("Read: %d\n", buffer_read(&cb));
    printf("Read: %d\n", buffer_read(&cb));
    printf("Read: %d\n", buffer_read(&cb));
}