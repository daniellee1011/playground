
#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

template <typename K, typename V>
class LRUCache {
	list<pair<K, V>> cacheList;
	unordered_map<K, typename list<pair<K, V>>::iterator> cacheMap;
	int capacity;
public:
	LRUCache(int capacity) { this->capacity = capacity; cout << "capacity: " << this->capacity << endl; };
	V get(K key) {
		cout << "get " << key << endl;
		if (cacheMap.find(key) == cacheMap.end()) return V();
		// Get Node
		auto node = cacheMap[key];
		// declare value to return - node.second
		int value = node->second;
		// erase the node at list
		cacheList.erase(node);
		// push new pair at the front of the list
		cacheList.push_front({key, value});
		// update the value at cacheMap
		cacheMap[key] = cacheList.begin();
		return value;
	}
	void put(K key, V value) {
		cout << "put " << key << " " << value << endl;
		if (cacheMap.find(key) != cacheMap.end()) {
			// get node
			auto node = cacheMap[key];
			// erase the node at the list
			cacheList.erase(node);
		}
		// push front new pair {key, value}
		cacheList.push_front({key, value});
		// insert new pair into cacheMap
		cacheMap[key] = cacheList.begin();
		
		// if the size of the list is bigger than the capacity
		if (cacheList.size() > capacity) {
		// get last node at the list
			auto node = --cacheList.end();
			//cacheList.pop_back();
		// erase last node at the map
			cacheMap.erase(node->first);
		// erase last node at the list
			//cacheList.erase(node);
			cacheList.pop_back();
		}
	}
};
// ["LRUCache","put","put","get","put","get","put","get","get","get"]
// [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
int main()
{
	LRUCache<int, int> lru(2);
	lru.put(1, 1);
	lru.put(2, 2);
	cout << lru.get(1) << endl;
	lru.put(3, 3);
	cout << lru.get(2) << endl;
	lru.put(4, 4);
	cout << lru.get(1) << endl;
	cout << lru.get(3) << endl;
	cout << lru.get(4) << endl;
	return 0;
}
