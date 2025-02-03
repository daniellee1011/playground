# 39. Combination Sum

from typing import List

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        result = []
        self.helper([], candidates, 0, 0, target, result)
        return result
    
    def helper(self, list_, candidates, index, total, target, result):
        if total == target:
            result.append(list_)
            return
        
        for i in range(index, len(candidates)):
            n = candidates[i]
            if total + n <= target:
                self.helper(list_ + [n], candidates, i, total + n, target, result)

if __name__ == "__main__":
    sol = Solution()

    candidates = [2,3,6,7]
    target = 7

    result = sol.combinationSum(candidates, target)
    print("Unique combinations of candidates: ", result)
