// 3. Longest Substring Without Repeating Characters

#include <iostream>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int longest = 0;
        std::unordered_map<char, int> set;
        int left = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.at(i);
            if (set.find(c) != set.end() && set[c] >= left) {
                left = set[c] + 1;
            }
            set[c] = i;
            longest = longest > i - left + 1 ? longest : i - left + 1;
        }

        return longest;
    }
};