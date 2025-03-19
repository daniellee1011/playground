#include <iostream>
#include <cstdint>
#include <vector>

#define SET(n, pos) ((n) | (1 << (pos)))
#define CHECK(n, pos) (((n) >> (pos)) & 1)
#define TOGGLE(n, pos) ((n) ^ (1 << (pos)))
#define CLEAR(n, pos) ((n) & ~(1 << (pos)))

using namespace std;

int countSetBits(uint32_t n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int detectPowerOfTwo(uint32_t n) {
    return (n & (n - 1)) == 0;
}

void swap(int &a, int &b) {
    a ^= b; // a = a ^ b
    b ^= a; // b = b ^ a = b ^ (a ^ b) = a
    a ^= b; // a = a ^ b = (a ^ b) ^ a = b
}

uint32_t revereseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = ((n >> i) & 1) | (result << 1);
    }
    return result;
}

int lowestSetBit(int n) {
    return n & -n;
}

int findUnique(vector<int> &nums) {
    int unique = 0;
    for (int &num : nums) {
        unique ^= num;
    }
    return unique;
}

int findOnes(vector<int> &nums) {
    int ones = 0;
    int twos = 0;
    for (int &num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
}

int hammingDistance(int n1, int n2) {
    return countSetBits(n1 ^ n2);
}

int main() {
    return 0;
}