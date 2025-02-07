#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        if (strs.size() == 0) return "";

        std::string result = strs[0];
        size_t right = result.length();
        for (std::string& s : strs) {
            right = std::min(s.length(), right);
            for (size_t i = 0; i < right ; i++) {
                if (result.at(i) != s.at(i)) {
                    right = i;
                    break;
                }
            }
        }

        return result.substr(0, right);
    }
};