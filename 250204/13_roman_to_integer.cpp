// 13. Roman to Integer

#include <iostream>
#include <unordered_map>

class Solution {
public:
    int romanToInt(std::string s) {
        std::unordered_map<char, int> um;
        um['I'] = 1;
        um['V'] = 5;
        um['X'] = 10;
        um['L'] = 50;
        um['C'] = 100;
        um['D'] = 500;
        um['M'] = 1000;

        int result = 0;
        // [1, 3999]
        for (int i = 0; i < s.length(); i++) {
            if (i < s.length() - 1 && um[s.at(i)] < um[s.at(i + 1)]) {
                result -= um[s.at(i)];
            } else {
                result += um[s.at(i)];
            }
        }
        
        return result;
    }
};