// 20. Valid Parentheses

#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    bool isValid(std::string s) {
        std::unordered_map<char, char> hm = {
            {'(',')'},
            {'{','}'},
            {'[',']'}
        };

        std::vector<char> stack;
        for (int i = 0; i < s.length(); i++) {
            if (hm.find(s.at(i)) != hm.end()) {
                stack.push_back(hm[s.at(i)]);
            } else {
                if (stack.empty()) return false;
                if (stack.back() == s.at(i)) {
                    stack.pop_back();
                } else {
                    return false;
                }
            }
        }

        return stack.empty() ? true : false;
    }
};