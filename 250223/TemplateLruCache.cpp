// #include <iostream>
// #include <list>
// #include <unordered_map>
// #include <typeinfo>
// #include <shared_mutex>

// using namespace std;

// template <typename K, typename V>
// class LRUCache {
// private:
//     int capacity;
//     list<pair<K, V>> cacheList;
//     unordered_map<K, typename list<pair<K, V>>::iterator> cacheMap;
//     mutable shared_mutex cacheMutex; // Use shared_mutex for better performance
// public:
//     LRUCache(int capacity) { this->capacity = capacity; }
//     V get(K key) {
//         shared_lock<shared_mutex> lock(cacheMutex); // Allow multiple readers

//         if (cacheMap.find(key) == cacheMap.end()) {
//             cerr << "Key doesn't exist" << endl;
//             return -1;
//         }
//         // Upgrade to exclusive lock to modify list order
//         lock.unlock();
//         unique_lock<shared_mutex> writeLock(cacheMutex);

//         // get node from the map
//         auto node = cacheMap[key];
//         // declare value to return with node->second
//         int value = node->second;
//         // erase the node at the list
//         cacheList.erase(node);
//         // push_front {key, value} at the list to update cache status
//         cacheList.push_front({key, value});
//         // update the map with front node
//         cacheMap[key] = cacheList.begin();
//         // return value
//         return value;
//     }
//     void put(K key, V value) {
//         unique_lock<shared_mutex> lock(cacheMutex); // Exclusive lock for writes
        
//         // if key exists
//         if (cacheMap.find(key) != cacheMap.end()) {
//         // get node from the map
//             auto node = cacheMap[key];
//         // erase the node at the list
//             cacheList.erase(node);
//         } else { // else
//         // if the size of cache == capacity
//             if (cacheList.size() == capacity) {
//         // get last node at the cacheList
//                 auto node = --cacheList.end();
//         // erase the key at the map
//                 cacheMap.erase(node->first);
//         // pop_back() the list
//                 cacheList.pop_back();
//             }
//         }
//         // push_front {key, value} into the list
//         cacheList.push_front({key, value});
//         // update the map with new node
//         cacheMap[key] = cacheList.begin();
//     }
    
//     void print() {
//         for (auto &node : cacheList) {
//             cout << typeid(node).name() << ": " << node.first << ": " << node.second << " -> ";
//         } cout << "NULL\n";
//     }
// };

// int main()
// {
//     std::cout << "hello, world" << std::endl;
    
//     LRUCache<int, int> lru(2);
//     lru.put(1, 10);
//     lru.put(2, 20);
    
//     lru.print();
    
//     int data = -2;
//     data = lru.get(1);
//     cout << "data: " << data << endl;
    
//     lru.print();
    
//     data = lru.get(3);
//     cout << "data: " << data << endl;
    
//     lru.put(3, 30);
    
//     lru.print();
    
//     return 0;
// }