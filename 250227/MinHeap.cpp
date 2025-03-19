#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MinHeap {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    void insert(int data) {
        minHeap.push(data);
    }
    int extractMin() {
        int data = minHeap.top();
        minHeap.pop();
        return data;
    }
};

int main() {
    MinHeap mh;
    mh.insert(5);
    mh.insert(2);
    mh.insert(9);
    mh.insert(1);
    int data = mh.extractMin();
    cout << "min value: " << data << endl;
    return 0;
}