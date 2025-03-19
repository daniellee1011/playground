// 381. Insert Delete GetRandom O(1) - Duplicates allowed

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class RandomizedCollection {
    unordered_map<int, unordered_set<int>> um;
    vector<int> vec;
public:
    RandomizedCollection(){}
    bool insert(int val) {
        bool tf = um.find(val) == um.end() ? true : false;
        um[val].insert(vec.size());
        vec.push_back(val);
        return tf;
    }
    
    bool remove(int val) {
        if (um.find(val) == um.end()) return false;
        if (val == vec.back()) {
            vec.pop_back();
            int lastIndex = vec.size();
            um[val].erase(lastIndex);
            if (um[val].size() == 0) um.erase(val);
            return true;
        }
        int index = *um[val].begin();
        um[val].erase(index);
        if (um[val].size() == 0) um.erase(val);
        int lastVal = vec.back();
        vec.pop_back();
        int lastIndex = vec.size();
        um[lastVal].erase(lastIndex);
        um[lastVal].insert(index);
        vec[index] = lastVal;
        return true;
    }
    
    int getRandom() {
        return vec[rand() % vec.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */