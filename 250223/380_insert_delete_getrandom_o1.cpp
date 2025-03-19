#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 0 2 4 5 7
// 0 1 2 3 4

class RandomizedSet {
private:
    unordered_map<int, int> um;
    vector<int> vec;
public:
    RandomizedSet() {};
    bool insert(int val) {
        if (um.find(val) != um.end()) {
            return false;
        }
        // key: val, value: index
        um[val] = vec.size();
        // insert at vec
        vec.push_back(val);
        return true;
    }
    bool remove(int val) {
        // not exist
        if (um.find(val) == um.end()) return false;
        int index = um[val];
        // get last value at vec
        int lastVal = vec.back();
        // push last value to val's vec position
        vec[index] = lastVal;
        // erase last vec
        vec.pop_back();
        // update last val at um
        um[lastVal] = index;
        // erase val at um
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