// 380. Insert Delete GetRandom O(1)

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
    unordered_map<int, int> um;
    vector<int> vec;

    public:
        RandomizedSet() {
            um.clear();
            vec.clear();
        }
        
        bool insert(int val) {
            if (um.find(val) != um.end()) {
                return false;
            }
            um[val] = vec.size();
            vec.push_back(val);
            return true;
        }
        
        bool remove(int val) {
            if (um.find(val) == um.end()) {
                return false;
            }
            // 0 1 2
            // 7 5 3
            // val = 7, index = 0
            int index = um[val];
            int lastIndex = vec.size() - 1;

            int lastVal = vec[lastIndex];
            vec[index] = lastVal;
            um[lastVal] = index;
            
            vec.pop_back();
            um.erase(val);
            return true;
        }
        
        int getRandom() {
            return vec[rand() % vec.size()];
        }
    };
    
int main() {
    return 0;
}