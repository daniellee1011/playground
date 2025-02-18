#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

void *optimized_memcpy(void *dest, void *src, size_t n) {
    uint64_t *dword_dest = (uint64_t*)dest;
    const uint64_t *dword_src = (const uint64_t*)src;
    size_t dword_count = n / 8;
    size_t remainder = n % 8;

    while (dword_count--) *dword_dest++ = *dword_src++;

    char *byte_dst = (char*)dword_dest;
    const char *byte_src = (const char*)dword_src;
    while (remainder--) *byte_dst = *byte_src;

    return dest;
}

int main() {
    char src[] = "Hello, optimized memcpy!";
    char dest1[50], dest2[50];

    memcpy(dest1, src, sizeof(src));
    printf("Standard memcpy result: %s\n", dest1);

    optimized_memcpy(dest2, src, sizeof(src));
    printf("Optimzed memcpy result: %s\n", dest2);


    if (strcmp(dest1, dest2) == 0) {
        printf("Both memcpy functions produce the same result!\n");
    } else {
        printf("Result differ!\n");
    }

    return 0;
}
