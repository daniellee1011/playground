// 53. Maximum Subarray

#include <iostream>
#include <vector>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int max_sum = nums[0];
        std::vector<int> max_presum;
        max_presum.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            int temp = max_presum[i - 1] > 0 ? max_presum[i - 1] : 0;
            temp = temp + nums[i] > nums[i] ? temp + nums[i] : nums[i];
            max_presum.push_back(temp);
            max_sum = max_sum > temp ? max_sum : temp;
        }
        return max_sum;
    }
};