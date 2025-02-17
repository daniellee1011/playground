#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

void *my_malloc(size_t size) {
    void *ptr = sbrk(size); // Increase data segment
    if (ptr == (void *)-1) {
        return NULL;
    }
    return ptr;
}

void *my_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void *my_memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d < s || d >= (s + n)) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }

    // Clear the remainint part of src
    if (dest > src) {
        size_t remaining = (size_t)((unsigned char *)dest - (unsigned char *)src);
        memset((unsigned char *)src, '\0', remaining);
    }

    return dest;
}

int main() {
    char buffer1[20] = "Hello, World!";
    char buffer2[20];

    my_memcpy(buffer2, buffer1, strlen(buffer1) + 1);
    printf("Copied String: %s\n", buffer2);

    char buffer3[] = "Overlap Test";
    my_memmove(buffer3 + 2, buffer3, strlen(buffer3) + 1);
    printf("Moved String: %s\n", buffer3);

    void *ptr = my_malloc(100);
    if (ptr) {
        printf("Memory allocated successfully\n");
    }

    return 0;
}
