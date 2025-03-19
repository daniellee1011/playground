#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity;
    // {key, value}
    list<pair<int, int>> cacheList;
    // key, {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            cerr << "Key doesn't exist" << endl;
            return -1;
        }
        // get value to return
        auto node = cacheMap[key];
        int value = node->second;
        // need to update cacheList
        cacheList.erase(node);
        cacheList.push_front({key, value});
        // update cacheMap with new node
        cacheMap[key] = cacheList.begin();
        return value;
    }
    void put(int key, int value) {
        // if key exists in value
        if (cacheMap.find(key) != cacheMap.end()) {
            // get node at the list to remove
            auto node = cacheMap[key];
            // erase at the list
            cacheList.erase(node);
        } else { // key doesn't exist
            // check the size of cache which shouldn't be over capacity
            if (cacheList.size() == capacity) { // if so
                // get last node at the list
                auto node = --cacheList.end();
                // erase the key at cacheMap
                cacheMap.erase(node->first);
                // erase it at the list
                cacheList.erase(node);
            }
        }
        // push_front new node to the list
        cacheList.push_front({key, value});
        // insert key to cacheMap
        cacheMap[key] = cacheList.begin();
    }
};

int main() {
    return 0;
}