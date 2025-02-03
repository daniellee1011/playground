// 2133. Check if Every Row and Column Contains All Numbers
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    bool checkValid(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            std::unordered_set<int> rowSet, colSet;
            for (int j = 0; j< n; j++) {
                // Insert values into the row column sets
                if (!rowSet.insert(matrix[i][j]).second || !colSet.insert(matrix[j][i]).second) {
                    return false; // Duplicate found
                }
            }
        }

        return true;
    }

    // Works, but not optimized
    bool _checkValid(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();

        std::unordered_map<int, int> um;
        for (int i = 1; i <= n; i++) {
            um[i] = 1;
        }

        for (int i = 0; i < n; i++) {
            std::unordered_map<int, int> copy_um = um;
            for (int j = 0; j < n; j++) {
                int val = matrix[i][j];
                if (copy_um.find(val) != copy_um.end()) {
                    copy_um.erase(val);
                } else {
                    return false;
                }
            }
            copy_um = um;
            for (int j = 0; j < n; j++) {
                int val = matrix[j][i];
                if (copy_um.find(val) != copy_um.end()) {
                    copy_um.erase(val);
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {3, 1, 2}, {2, 3, 1}};
    std::cout << std::boolalpha << sol.checkValid(matrix) << std::endl; // Output: true
    return 0;
}