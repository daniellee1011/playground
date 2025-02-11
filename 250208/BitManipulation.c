#include <stdio.h>

int multiply(int a, int b) {
    int result = 0;
    while (b > 0) {
        if (b & 1) result += a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}

// 10111
// rev  0     1    11  111 1110 11101
// temp 10111 1011 101 10  1    0
// 10101
// rev  0     1    10  101 1010 10101
// temp 10101 1010 101 10  1    
int is_bitwise_palindrome(int x) {
    int rev = 0, temp = x;
    while (temp) {
        rev = (rev << 1) | (temp & 1);
        temp >>= 1;
    }
    return rev == x;
}

unsigned int reverseBitsPowerOf2(unsigned int num) {
    int pos = __builtin_ctz(num); // Count trailing zeroes to get bit position
    return 1 << (31 - pos);
}

int countSetBits(int n) {
    int count = 0;
    while (n > 0) {
        count += (n & 1);
        n >>= 1;
    }
    return count;
}