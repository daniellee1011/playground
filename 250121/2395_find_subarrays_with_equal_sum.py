# 2395. Find Subarrays With Equal Sum

from typing import List

class Solution:
    # O (n)
    def findSubarrays(self, nums: List[int]) -> bool:
        seen = set()
        for i in range(len(nums) - 1):
            sum_ = nums[i] + nums[i + 1]
            if sum_ in seen:
                return True
            seen.add(sum_)
        return False


    # O (n ^ 2), inefficient solution
    def _findSubarrays(self, nums: List[int]) -> bool:
        for i in range(len(nums) - 2):
            sum_ = nums[i] + nums[i + 1]
            for j in range(i + 1, len(nums) - 1):
                if sum_ == nums[j] + nums[j + 1]:
                    return True
        return False
    
if __name__ == "__main__":
    sol = Solution()

    nums = [4, 2, 4]
    if True == sol.findSubarrays(nums):
        print("Pass")
    else:
        print("Fail")

    nums = [1, 2, 3, 4, 5]
    if False == sol.findSubarrays(nums):
        print("Pass")
    else:
        print("Fail")

    nums = [0, 0, 0]
    if True == sol.findSubarrays(nums):
        print("Pass")
    else:
        print("Fail")