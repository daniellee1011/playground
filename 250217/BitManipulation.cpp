#include <iostream>
#include <vector>

using namespace std;

int singleNumber(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int x : nums) {
        ones = (ones ^ x) & ~twos;
        twos = (twos ^ x) & ~ones;
    }
    return ones;
}

int main() {
    vector<int> nums = {5, 5, 5, 7, 3, 3, 3};
    cout << "Single number is: " << singleNumber(nums) << endl;
    return 0;
}
