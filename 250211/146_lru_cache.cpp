#include <iostream>
#include <list>
#include <unordered_map>

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
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

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

int main() {
    LRUCache cache(2);  // Capacity of 2

    cache.put(1, 10);
    cache.put(2, 20);

    std::cout << "Get 1: " << cache.get(1) << std::endl;  // Should return 10 (moves key 1 to front)

    cache.put(3, 30);  // Evicts key 2 (Least Recently Used)

    std::cout << "Get 2: " << cache.get(2) << std::endl;  // Should return -1 (not found)
    std::cout << "Get 3: " << cache.get(3) << std::endl;  // Should return 30

    cache.put(4, 40);  // Evicts key 1

    std::cout << "Get 1: " << cache.get(1) << std::endl;  // Should return -1 (not found)
    std::cout << "Get 3: " << cache.get(3) << std::endl;  // Should return 30
    std::cout << "Get 4: " << cache.get(4) << std::endl;  // Should return 40

    return 0;
}
