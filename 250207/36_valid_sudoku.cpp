#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
    public:
        bool isValidSudoku(std::vector<std::vector<char>>& board) {
            std::vector<std::unordered_set<char>> boxes(9), rows(9), cols(9);

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    char c = board[i][j];
                    if (c != '.') {
                        if (rows[i].find(c) == rows[i].end()) {
                            rows[i].insert(c);
                        } else {
                            return false;
                        }
                        if (cols[j].find(c) == cols[j].end()) {
                            cols[j].insert(c);
                        } else {
                            return false;
                        }
                        int boxIndex = (i / 3) * 3 + (j / 3);
                        if (boxes[boxIndex].find(c) == boxes[boxIndex].end()) {
                            boxes[boxIndex].insert(c);
                        } else {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
    };