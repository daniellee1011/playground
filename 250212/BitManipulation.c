#include <stdio.h>

int multiply(int a, int b) {
    int result;
    while (b > 0) {
        if (b & 1) result += a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}

int is_bitwise_palindrome(int x) {
    int rev = 0, temp = x;
    while (temp > 0) {
        rev = (rev << 1) | (temp & 1);
        temp >>= 1;
    }
    return rev == x;
}

int countSetBits(int n) {
    int count = 0;
    while (n > 0) {
        if (n & 1) count++;
        n >>= 1;
    }
    return count;
}

int main() {
    int n1 = 2;
    int n2 = 7;
    printf("is paline: %d\n", is_bitwise_palindrome(n1));
    printf("is paline: %d\n", is_bitwise_palindrome(n2));

    printf("count set bits: %d\n", countSetBits(n1));
    printf("count set bits: %d\n", countSetBits(n2));

    return 0;
}