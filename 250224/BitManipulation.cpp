#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>

#define SET(n, pos) ((n) | (1 << (pos)))
#define CLEAR(n, pos)  ((n) & ~(1 << (pos)))
#define TOGGLE(n, pos) ((n) ^ (1 << (pos)))
#define CHECK(n, pos) ((n) >> (pos) & 1)

using namespace std;

bool isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 8; i++) {
        result = ((n >> i) & 1) | (result << 1);
    }
    return result;
}

bool isOdd(int n) {
    return n & 1;
}

int hammingDistance(uint32_t n1, uint32_t n2) {
    int dist = 0;
    for (int i = 0; i < 32; i++) {
        dist += (n1 & 1) ^ (n2 & 1);
        n1 >>= 1;
        n2 >>= 1;
    }
    return dist;
}

int hammingWeight(int n) {
    int weight = 0;
    while (n > 0) {
        weight += n & 1;
        n >>= 1;
    }
    return weight;
}

int uniqueNumber(vector<int> &nums) {
    int unique = 0;
    for (int num : nums) {
        unique ^= num;
    }
    return unique;
}

int singleNumber(vector<int> &nums) {
    int ones = 0, twos = 0;

    for (int num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }

    return ones;
}

void swap(int &n1, int &n2) {
    n1 ^= n2;
    n2 ^= n1;
    n1 ^= n2;
}

int main() {
    uint32_t n = 13;
    cout << "n: " << bitset<16>(n) << endl;
    reverseBits(n);

    cout << "hammingWeight: " << hammingWeight(n) << endl;

    vector<int> vec1 = {3, 3, 2, 2, 1, 2, 4, 3, 4, 4};
    cout << "singleNumber: " << singleNumber(vec1) << endl;

    vector<int> vec2 = {3, 2, 3, 4, 4, 1, 5, 1, 5};
    cout << "uniqueNumber: " << uniqueNumber(vec2) << endl;

    return 0;
}