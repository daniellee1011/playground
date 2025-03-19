#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class Solution {
    public:
        struct Compare {
            bool operator()(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
                if (a.first == b.first) {
                    return a.second > b.second;
                }
                return a.first < b.first;
            }
        };

        std::vector<std::string> topKFrequent(std::vector<std::string>& words, int k) {
            std::vector<std::string> vec;
            std::unordered_map<std::string, int> um;

            for (std::string &word : words) {
                um[word]++;
            }

            std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, Compare> pq;
            
            for (auto& pair : um) {
                pq.push({pair.second, pair.first});
            }

            for (int i = 0; i < k; i++) {
                vec.push_back(pq.top().second);
                pq.pop();
            }

            return vec;
        }
    };

    int main() {
        Solution sol;
        std::vector<std::string> words1 = {"i", "love", "leetcode", "i", "love", "coding"};
        int k1 = 2;
        std::vector<std::string> result1 = sol.topKFrequent(words1, k1);
    
        std::cout << "Top " << k1 << " frequent words: ";
        for (const std::string& word : result1) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    
        std::vector<std::string> words2 = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
        int k2 = 4;
        std::vector<std::string> result2 = sol.topKFrequent(words2, k2);
    
        std::cout << "Top " << k2 << " frequent words: ";
        for (const std::string& word : result2) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    
        return 0;
    }