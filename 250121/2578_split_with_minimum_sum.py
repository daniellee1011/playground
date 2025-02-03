# 2578. Split With Minimum Sum

class Solution:
    def splitNum(self, num: int) -> int:
        nums = []
        n = num
        while n > 0:
            nums.append(n % 10)
            n //= 10
        nums.sort()
        n1, n2 = "", ""
        for i, n in enumerate(nums):
            if i % 2 == 0:
                n1 += str(n)
            else:
                n2 += str(n)
        return int(n1) + int(n2)