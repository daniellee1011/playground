// 42. Trapping Rain Water

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int trap(std::vector<int>& height) {
        if (height.size() < 2) return 0;
        int water = 0;
        int left = 0, right = height.size() - 1;
        int lmax = height[left], rmax = height[right];

        while (left < right) {
            if (lmax < rmax) {
                left++;
                lmax = std::max(lmax, height[left]);
                water += lmax - height[left];
            } else {
                right--;
                rmax = std::max(rmax, height[right]);
                water += rmax - height[right];
            }
        }

        return water;
    }
};