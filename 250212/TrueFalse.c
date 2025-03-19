#include <stdio.h>

int main() {
    int tf = -1;
    
    if (tf) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    int a = 10;
    int *p = &a;
    int &ref = a;
    printf("p val, ref val: %d, %d\n", *p, ref);

    return 0;
}