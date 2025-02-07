// 560. Subarray Sum Equals K

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        int count = 0;
        std::unordered_map<int, int> hm;
        hm[0] = 1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            int temp = sum - k;
            if (hm.find(temp) != hm.end()) {
                count += hm[temp];
            }
            hm[sum] += 1;
        }
        return count;
    }
};