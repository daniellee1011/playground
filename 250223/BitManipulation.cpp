#include <iostream>
#include <vector>
#include <cstdint>

#define SET_BIT(x, pos) ((x) | (1 << (pos))) // Set bit at position 'pos'
#define CLEAR_BIT(x, pos) ((x) & ~(1 << (pos))) // Clear bit at position 'pos'
#define TOGGLE_BIT(x, pos) ((x) ^ (1 << (pos))) // Toggle bit at position 'pos'
#define CHECK_BIT(x, pos) (((x) >> (pos)) & 1) // Check if bit at 'pos' is set

int countSetBits(uint32_t n) {
    int count = 0;
    while (n > 0) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

void swap(int &a, int &b) {
    a ^= b; // a = a ^ b;
    b ^= a; // b = b ^ (a ^ b) -> a
    a ^= b; // a = (a ^ b) ^ (b ^ (a ^ b))
}

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result |= ((n >> i) & 1) << (31 - i);
    }
    return result;
}

// 10100
// 01011 + 1 = 01100
int lowestSetBit(int n) {
    return n & -n;
}

// Find a unique number in an array where every other number appears twice
int findUnique(std::vector<int>& nums) {
    int unique = 0;
    for (int num : nums) {
        unique ^= num;
    }
    return unique;
}

// Find the single number that appears once while others appear three times
int singleNumber(std::vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
}

int main() {
    std::vector<int> nums = {3, 2, 3, 4, 4, 3, 2, 5, 1, 1, 1};
    singleNumber(nums);
    return 0;
}