#include <iostream>
#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;

        auto node = cacheMap[key];
        std::pair<int, int> keyValue = *node;
        cacheList.erase(node);
        cacheList.push_front(keyValue);
        cacheMap[key] = cacheList.begin();

        return keyValue.second;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            auto node = cacheMap[key];
            cacheList.erase(node);
            cacheList.push_front({key, value});
            cacheMap[key] = cacheList.begin();
            return;
        }

        if (cacheList.size() == capacity) {
            auto lru = cacheList.back();
            cacheMap.erase(lru.first);
            cacheList.pop_back();
        }

        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};