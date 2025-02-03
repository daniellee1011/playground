#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> vec;
        helper(candidates, vec, result, 0, 0, target);
        return result;
    }

    void helper(std::vector<int>& candidates, std::vector<int>& vec, std::vector<std::vector<int>> &result, int index, int total, int target) {
        if (total == target) {
            result.push_back(vec);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            int val = candidates[i];
            if (total + val <= target) {
                vec.push_back(val);
                helper(candidates, vec, result, i, total + val, target);
                vec.pop_back();
            }
        }

    }

    void printResult(const std::vector<std::vector<int>> result) {
        std::cout << "Unique combinations: \n";
        for (const auto& res : result) {
            std::cout << "[";
            for (int num : res) std:: cout << num << " ";
            std::cout << "]\n";
        }
    }
};

int main() {
    Solution sol;
    std::vector<int> candidates = {2,3,6,7};
    int target = 7;

    std::vector<std::vector<int>> result = sol.combinationSum(candidates, target);
    sol.printResult(result);
    
    return 0;
}