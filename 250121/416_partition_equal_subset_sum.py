# 416. Partition Equal Subset Sum

from typing import List

class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        sum_ = sum(nums)
        if sum_ % 2 == 1:
            return False
        half = sum_ // 2
        dp = [False] * (half + 1)
        dp[0] = True
        for n in nums:
            for j in range(half, n - 1, -1):
                dp[j] = dp[j] or dp[j - n]
        return dp[half]
    
if __name__ == "__main__":
    sol = Solution()

    nums = [1, 5, 11, 5]
    print(sol.canPartition(nums))