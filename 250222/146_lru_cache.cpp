// 146. LRU Cache

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
    int capacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

    public:
        LRUCache(int capacity) { this->capacity = capacity; }
        
        int get(int key) {
            // if not exists return -1
            if (cacheMap.find(key) == cacheMap.end()) return -1;
            // else
            // get node
            auto node = cacheMap[key];
            // declare value variable to return and assign the value to the variable
            int value = node->second;
            // erase the node at the list
            cacheList.erase(node);
            // push front new node to the list
            cacheList.push_front({key, value});
            // update the map with new node
            cacheMap[key] = cacheList.begin();
            // return value
            return value;
        }
        
        void put(int key, int value) {
            // if key exists in the map
            if (cacheMap.find(key) != cacheMap.end()) {                
                // get a node having key
                auto node = cacheMap[key];
                // erase the node at the list
                cacheList.erase(node);
            }
            // push_front new node {key, value} to the list
            cacheList.push_front({key, value});
            // insert new node to the map
            cacheMap[key] = cacheList.begin();
            // if the size of the list is bigger than capacity
            if (cacheList.size() > capacity) {
                // get last node at the list
                auto node = --cacheList.end();
                // erase the node at the map using key
                cacheMap.erase(node->first);
                // erase the node at the list
                cacheList.pop_back();
            }
        }
    };
    
    /**
     * Your LRUCache object will be instantiated and called as such:
     * LRUCache* obj = new LRUCache(capacity);
     * int param_1 = obj->get(key);
     * obj->put(key,value);
     */