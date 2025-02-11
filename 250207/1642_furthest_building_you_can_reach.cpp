#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    int furthestBuilding(std::vector<int>& heights, int bricks, int ladders) {
        int pos = 0;
        std::priority_queue<int> minHeap;

        for (int i = 1; i < heights.size(); i++) {
            int diff = heights[i] - heights[i - 1];
            if (diff > 0) {
                minHeap.push(diff);
                if (minHeap.size() > ladders) {
                    bricks -= minHeap.top();
                    minHeap.pop();
                    if (bricks < 0) {
                        return i;
                    }
                }
            }
        }

        return heights.size() - 1;
    }
};