#include <stdio.h>

void PointerPrint(int *p) {
    printf("Value in Pointer: %d\n", *p);
}

void increment(int *p) {
    (*p)++;
}

int main() {
    int num = 5;
    printf("Original num: %d\n", num);
    int *p = &num;
    *p = 10;
    PointerPrint(&num);
    increment(p);
    printf("After incrementing num: %d\n", num);
    return 0;
}
