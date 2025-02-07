#include <iostream>
#include <vector>
#include <queue>

class Solution {
private:
    int m;
    int n;
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int count = 0;
        m = grid.size();
        n = grid[0].size();

        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    count++;
                    visited[i][j] = true;
                    dfs(i, j, grid, visited);
                }
            }
        }

        return count;
    }

    void dfs(int c, int r, std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited) {
        std::vector<std::pair<int, int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < dir.size(); i++) {
            int nc = c + dir[i].first;
            int nr = r + dir[i].second;

            if (0 <= nc && nc < m && 0 <= nr && nr < n) {
                if (grid[nc][nr] == '1' && !visited[nc][nr]) {
                    visited[nc][nr] = true;
                    dfs(nc, nr, grid, visited);
                }
            }
        }
    }
};