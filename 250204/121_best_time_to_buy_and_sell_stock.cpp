#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int max_profit = 0;
        std::vector<int> s;

        for (int i = 0; i < prices.size(); i++) {
            if (s.empty()) s.push_back(prices[i]);
            if (prices[i] > s.back()) {
                max_profit = max_profit > prices[i] - s.front() ? max_profit : prices[i] - s.front();
                s.push_back(prices[i]);
            } else {
                while (!s.empty() && s.back() >= prices[i]) {
                    s.pop_back();
                }
                s.push_back(prices[i]);
            }
        }

        return max_profit;
    }
};