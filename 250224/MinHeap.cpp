#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Compare {
    bool operator()(int left, int right) {
        return left > right; // Min-Heap
    }
};

class MinHeap {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    void insert(int n) {
        minHeap.push(n);
    }
    int extractMin() {
        if (minHeap.empty()) throw runtime_error("Heap Empty!");
        int data = minHeap.top();
        minHeap.pop();
        return data;
    }
};

int main() {
    MinHeap heap;
    heap.insert(5);
    heap.insert(2);
    heap.insert(3);
    heap.insert(9);
    int minVal = heap.extractMin();
    cout << "minVal: " << minVal << endl;

    priority_queue<int> pq;
    pq.push(5);
    pq.push(1);
    pq.push(9);
    cout << "pq top: " << pq.top() << endl;

    priority_queue<int, vector<int>, less<int>>  pq2;
    pq2.push(5);
    pq2.push(1);
    pq2.push(9);
    cout << "pq2 top: " << pq2.top() << endl;

    priority_queue<int, vector<int>, Compare> compMinHeap;
    compMinHeap.push(4);
    compMinHeap.push(1);
    compMinHeap.push(6);
    cout << "compMinHeap: " << compMinHeap.top() << endl;
    
    return 0;
}