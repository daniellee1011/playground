#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet {
    unordered_map<int, int> um;
    vector<int> vec;
    public:
        RandomizedSet() {}
        bool insert(int val) {
            if (um.find(val) != um.end()) return false;
            um[val] = vec.size();
            vec.push_back(val);
            return true;
        }
        
        bool remove(int val) {
            if (um.find(val) == um.end()) return false;
            int index = um[val];
            int lastVal = vec.back();
            vec.pop_back();
            int lastIndex = vec.size();
            um[lastVal] = index;
            vec[index] = lastVal;
            um.erase(val);
            return true;
        }
        
        int getRandom() {
            return vec[rand() % vec.size()];
        }
    };
    
    /**
     * Your RandomizedSet object will be instantiated and called as such:
     * RandomizedSet* obj = new RandomizedSet();
     * bool param_1 = obj->insert(val);
     * bool param_2 = obj->remove(val);
     * int param_3 = obj->getRandom();
     */

int main() {
    return 0;
}