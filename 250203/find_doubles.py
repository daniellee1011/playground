from typing import List
from collections import defaultdict

def find_doubles(nums: List[int]) -> List[int]:
    dic = defaultdict(int)
    for n in nums:
        dic[n] += 1
    set_ = set()
    for n in nums:
        if dic[n] == 1:
            set_.add(n)
    print(set_)
    result = []
    for n in set_:
        double = n * 2
        if double in set_:
            result.append(n)

    return result

if __name__ == "__main__":
    nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 8]
    print(find_doubles(nums))