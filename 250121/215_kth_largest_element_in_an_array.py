# 215. Kth Largest Element in an Array

from typing import List
import heapq

class Solution:
    # O (n log k)
    def findKthLargest(self, nums: List[int], k: int) -> int:
        heap = nums[:k]
        heapq.heapify(heap)
        for n in nums[k:]:
            if n > heap[0]:
                heapq.heappushpop(heap, n)
        return heap[0]

    # O (n + k log n)
    def _findKthLargest(self, nums: List[int], k: int) -> int:
        heap = [- n for n in nums]
        heapq.heapify(heap)
        print(heap)
        result = 0
        for i in range(k):
            result = -heapq.heappop(heap)
        return result
        
if __name__ == "__main__":
    sol = Solution()

    nums = [3, 2, 1, 5, 6, 4]
    k = 2
    print(sol.findKthLargest(nums, k))

    nums = [3,2,3,1,2,4,5,5,6]
    k = 4
    print(sol.findKthLargest(nums, k))