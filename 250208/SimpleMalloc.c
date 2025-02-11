#include <stdio.h>

#define HEAP_SIZE 1024

char heap[HEAP_SIZE]; // Simulated heap

void *simple_malloc(size_t size) {
    static int offset = 0;
    if (offset + size > HEAP_SIZE) return NULL; // Out of memory
    void *ptr = &heap[offset];
    offset += size;
    return ptr;
}

