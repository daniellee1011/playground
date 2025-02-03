# 494. Target Sum

from typing import List

class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        dp = {}
        return self.helper(nums, target, dp, 0, 0)
    
    def helper(self, nums, target, dp, index, val):
        if index == len(nums):
            return 1 if val == target else 0
        
        if (index, val) in dp:
            return dp[(index, val)]
        
        num = nums[index]
        
        add = self.helper(nums, target, dp, index + 1, val + num)
        sub = self.helper(nums, target, dp, index + 1, val - num)

        dp[(index, val)] = add + sub

        return dp[(index, val)]

    # Time Limit Exceeded
    def _findTargetSumWays(self, nums: List[int], target: int) -> int:
        result = []
        self._helper(0, "", 0, result, nums, target)
        return len(result)
    
    def _helper(self, val, string, index, result, nums, target):
        if index == len(nums):
            if val == target:
                result.append(string)
            return

        num = nums[index]
        self._helper(val + num, string + "+ " + str(num), index + 1, result, nums, target)
        self._helper(val - num, string + "- " + str(num), index + 1, result, nums, target)

if __name__ == "__main__":
    sol = Solution()

    nums = [1, 1, 1, 1, 1]
    target = 3
    print(sol.findTargetSumWays(nums, target))

    nums = [1]
    target = 1
    print(sol.findTargetSumWays(nums, target))