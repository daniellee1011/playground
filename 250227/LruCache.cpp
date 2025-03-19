#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }
        auto node = cacheMap[key];
        int value = node->second;
        cacheList.erase(node);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
        return value;
    }
    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            auto node = cacheMap[key];
            cacheList.erase(node);
        } else {
            if (cacheList.size() == capacity) {
                auto node = --cacheList.end();
                cacheMap.erase(node->first);
                cacheList.pop_back();
            }
        }
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};

int main() {
    return 0;
}