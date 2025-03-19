#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class Solution {
public:
    struct Compare {
        bool operator()(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first < b.first;
        }
    };

    std::vector<std::string> topKFrequent(std::vector<std::string>& words, int k) {
        std::vector<std::string> vec;
        return vec;
    }
};