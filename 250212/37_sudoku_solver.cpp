// 37. Sudoku Solver

#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool isValid(std::vector<std::vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == c || board[i][col] == c || board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == c) {
                return false;
            }
        }
        return true;
    }

    bool backtracking(std::vector<std::vector<char>>& board, int row, int col) {
        if (row == 9) return true;
        if (col == 9) return backtracking(board, row + 1, 0);
        if (board[row][col] != '.') return backtracking(board, row, col + 1);

        for (char c = '1'; c <= '9'; c++) {
            if (isValid(board, row, col, c)) {
                board[row][col] = c;
                if (backtracking(board, row, col + 1)) return true;
                board[row][col] = '.';
            }
        }
        return false;
    }

    void solveSudoku(std::vector<std::vector<char>>& board) {
        backtracking(board, 0, 0);
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

    sol.solveSudoku(board);
    return 0;
}