from typing import List

class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        memo = {}
        result = self.helper(0, 0, nums, target, memo)
        print(memo)
        return result
    
    def helper(self, index, val, nums, target, memo):
        print(index, val, memo)
        if index == len(nums):
            return 1 if val == target else 0
        
        if (index, val) in memo:
            return memo[(index, val)]
        
        num = nums[index]

        add = self.helper(index + 1, val + num, nums, target, memo)
        sub = self.helper(index + 1, val - num, nums, target, memo)

        memo[(index, val)] = add + sub

        return memo[(index, val)]
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.findTargetSumWays([1, 1, 1, 1, 1], 3))