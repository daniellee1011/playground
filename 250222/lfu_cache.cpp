#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

// hash map: key, {value, frequency}
// hash map: frequency, list - for handling keys having same frequency with lru
// hash map: key to iter

class LFUCache {
    int capacity, min_freq;
    unordered_map<int, pair<int, int>> key_to_val;
    unordered_map<int, list<int>> freq_to_keys;
    unordered_map<int, list<int>::iterator> key_to_iter;
public:
    LFUCache(int capacity) : capacity(capacity), min_freq(1) {}

    int get(int key) {
        if (key_to_val.find(key) == key_to_val.end()) {
            cerr << key << " doesn't exist" << endl;
            return -1;
        }
        // get pair at key_to_val to return
        pair<int, int> pair_ = key_to_val[key];
        // declare value to return and assign the value at the pair
        int value = pair_.first;
        // get the freq
        int freq = pair_.second;
        // cout << "get freq: " << freq << endl;
        // check and update min_freq
        auto node = key_to_iter[key];
        // erase the node
        freq_to_keys[freq].erase(node);
        // erase the key if the size of list is 0
        if (freq_to_keys[freq].empty()) {
            freq_to_keys.erase(freq);
            if (!freq_to_keys.empty()) {
                min_freq = freq_to_keys.begin()->first;
            }
        }
        // insert new node with updated frequency into new frequency key
        freq_to_keys[freq + 1].push_front(key);
        // update key_to_iter with new node
        key_to_iter[key] = freq_to_keys[freq + 1].begin();
        // update key_to_val
        key_to_val[key] = {value, freq + 1};
        // return value variable
        return value;
    }

    void put(int key, int value) {
        if (key_to_val.find(key) != key_to_val.end()) {
            key_to_val[key].first = value;
            get(key);
            return;
        } 

        if (key_to_val.size() == capacity) {
            // get key and node to delete by using min_freq 
            // get key at freq_to_keys
            int key = freq_to_keys[min_freq].back();
            // erase the node at freq_to_keys
            freq_to_keys[min_freq].pop_back();
            // erase the node at key_to_iter
            key_to_iter.erase(key);
            // erase the pair at key_to_val
            key_to_val.erase(key);
            if (freq_to_keys[min_freq].empty()) {
                freq_to_keys.erase(min_freq);
            }
        }

        // put new pair to key_to_val
        key_to_val[key] = {value, 1};
        // push_front new node into freq_to_keys
        freq_to_keys[1].push_front(key);
        // update key_to_iter with new node
        key_to_iter[key] = freq_to_keys[1].begin();
        min_freq = 1;
    }

    void print() {
        cout << "min_freq: " << min_freq << endl;
        for (auto &pair : key_to_val) {
            cout << "key, value, freq: " << pair.first << " " << pair.second.first << " " << pair.second.second << endl;
        }
        for (auto &list_ : freq_to_keys) {
            cout << "freq: " << list_.first << " - ";
            for (auto &node : list_.second) {
                cout << node << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    LFUCache lfu(2);

    lfu.put(1, 10);
    lfu.put(2, 20);
    lfu.print();

    lfu.get(2);
    lfu.get(1);
    lfu.print();

    lfu.get(3);

    lfu.put(1, 100);
    lfu.print();

    lfu.get(1);
    lfu.get(1);

    lfu.get(2);
    lfu.get(2);
    lfu.get(2);

    return 0;
}