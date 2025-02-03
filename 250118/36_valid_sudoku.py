from typing import List
from collections import defaultdict

class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rowDic = defaultdict(set)
        colDic = defaultdict(set)
        boxDic = defaultdict(set)

        n = len(board)
        for i in range(n):
            for j in range(n):
                val = board[i][j]
                if val == '.':
                    continue

                if val not in rowDic[i]:
                    rowDic[i].add(val)
                else:
                    return False
                
                if val not in colDic[j]:
                    colDic[j].add(val)
                else:
                    return False
                
                box = (i // 3) * 3 + (j // 3)
                if val not in boxDic[box]:
                    boxDic[box].add(val)
                else:
                    return False
        
        return True
    
if __name__ == "__main__":
    sol = Solution()

    board = [
        ["5","3",".",".","7",".",".",".","."]
        ,["6",".",".","1","9","5",".",".","."]
        ,[".","9","8",".",".",".",".","6","."]
        ,["8",".",".",".","6",".",".",".","3"]
        ,["4",".",".","8",".","3",".",".","1"]
        ,["7",".",".",".","2",".",".",".","6"]
        ,[".","6",".",".",".",".","2","8","."]
        ,[".",".",".","4","1","9",".",".","5"]
        ,[".",".",".",".","8",".",".","7","9"]
    ]

    result = sol.isValidSudoku(board)
    print("Is the given Sudoku board valid?", result)
    
