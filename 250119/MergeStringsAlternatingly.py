# Merge Strings Alternatingly
# Given two strings, merge them by alternating characters.
# If one string is longer, append the remaining characters at the end.

# Input: s1 = "abc", s2 = "xyz"
# Output: "axbycz"

# Input: s1 = "abc", s2 = "pqrstu"
# Output: "apbqcrstu"

class Solution:
    def solution(self, s1, s2):
        result = ""
        i = 0
        while i < min(len(s1), len(s2)):
            result += s1[i] + s2[i]
            i += 1
        
        if i < len(s1):
            result += s1[i:]
        elif i < len(s2):
            result += s2[i:]

        return result
    
if __name__ == "__main__":
    sol = Solution()
    s1 = "abc"
    s2 = "xyz"
    result = sol.solution(s1, s2)
    print("Result: ", result)

    s1 = "abc"
    s2 = "pqrstu"
    result = sol.solution(s1, s2)
    print("Result: ", result)
