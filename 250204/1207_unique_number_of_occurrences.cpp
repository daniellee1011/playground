// 1207. Unique Number of Occurrences

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    bool uniqueOccurrences(std::vector<int>& arr) {
        std::unordered_map<int, int> um;

        for (int i = 0; i < arr.size(); i++) {
            um[arr[i]] += 1;
        }

        std::unordered_map<int, int> set;
        for (auto pair : um) {
            if (set.find(pair.second) != set.end()) {
                return false;
            } 
            set[pair.second] = 1;
        }

        return true;
    }
};