// 26. Remove Duplicates from Sorted Array

#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() == 1) return 1;

        int left = 0;
        int right = 1;

        while (right < nums.size()) {
            if (nums[left] == nums[right]) {
                nums.erase(nums.begin() + right);
            } else {
                left++;
                right++;
            }
        }

        return right;
    }
};