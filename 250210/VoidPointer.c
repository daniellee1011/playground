#include <stdio.h>

int main() {
    int a = 5;
    double b = 3.233;
    void *vp;

    vp = &a;
    printf("a = %d\n", *(int *)vp);

    vp = &b;
    printf("b = %f\n", *((double *)vp));

    return 0;
}