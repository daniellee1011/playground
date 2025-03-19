#include <iostream>
#include <cstddef>

using namespace std;

class MemoryPool {
private:
    struct Block {
        Block *next;
    };

    Block *freeList;
    char *pool;
    size_t blockSize;
    size_t numBlocks;
public:
    MemoryPool(size_t blockSize, size_t numBlocks) {
        this->blockSize = blockSize;
        this->numBlocks = numBlocks;
        pool = new char[blockSize * numBlocks];
        for (size_t i = 0; i < numBlocks; i++) {
            Block *block = reinterpret_cast<Block*>(pool + i * blockSize);
            block->next = freeList;
            freeList = block;
        }
    }
    ~MemoryPool() { delete[] pool; }
    void* allocate() {
        if (!freeList) {
            cerr << "Out of memory!" << endl;
            return nullptr;
        }
        Block *block = freeList;
        freeList = freeList->next;
        return block;
    }
    void deallocate(void *ptr) {
        Block *block = reinterpret_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }
};

int main() {
    MemoryPool pool(32, 10);
    
    void* mem1 = pool.allocate();
    void* mem2 = pool.allocate();

    pool.deallocate(mem1);
    pool.deallocate(mem2);
    
    return 0;
}