#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::unordered_set<char> rowSet[9], colSet[9], boxSet[9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char val = board[i][j];
                if (val == '.') continue;
                
                if (!rowSet[i].insert(val).second) {
                    return false;
                }

                if (!colSet[j].insert(val).second) {
                    return false;
                }

                int box = (i / 3) * 3 + (j / 3);
                if (!boxSet[box].insert(val).second) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
    Solution sol;

    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    std::cout << "Is the given Sudoku board valid? " << std::boolalpha << sol.isValidSudoku(board) << std::endl;

    return 0;
}