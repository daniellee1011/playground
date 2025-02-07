#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
private:
    std::vector<std::vector<int>> result;
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::unordered_map<int, int> hm;
        for (int& c : candidates) {
            hm[c] = 1;
        }

        std::vector<int> order;
        for (auto& pair : hm) {
            order.push_back(pair.first);
        }

        std::vector<int> vec;
        helper(0, target, vec, order);
        return result;
    }

    void helper(int index, int rem, std::vector<int> &vec, std::vector<int>& order) {
        if (rem == 0) {
            result.push_back(vec);
        }
        for (int i = index; i < order.size(); i++) {
            if (rem - order[i] >= 0) {
                vec.push_back(order[i]);
                helper(i, rem - order[i], vec, order);
                vec.pop_back();
            }
        }
    }
};