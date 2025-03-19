// #include <iostream>
// #include <sys/mman.h>
// #include <unistd.h>
// #include <cstdlib>
// #include <cstring>

// class SimpleAllocator {
// private:
//     struct Block {
//         size_t size;
//         bool free;
//         Block* next;
//     };
//     Block* freeList = nullptr;
// public:
//     // Allocate memory (similar to malloc)
//     void* allocator(size_t size) {
//         size_t totalSize = sizeof(Block) + size; // Include metadata

//         // Try to find a free block in the free list
//         Block* block = freeList;
//         Block* prev = nullptr;
//         while (block) {
//             if (block->free && block->size > size) {
//                 block->free = false;
//                 return (void *)(block + 1); // Return pointer after metadata
//             }
//             prev = block;
//             block = block->next;
//         }
//         // No free block found, allocate using mmap
//         void* ptr = mmap(nullptr, totalSize, PROT_READ | PROT_WRITE,
//                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//         if (ptr == MAP_FAILED) {
//             return nullptr; // mmap failed
//         }
//         // Create block metadata
//         block = (Block*)ptr;
//         block->size = size;
//         block->free = false;
//         block->next = nullptr;
//         // Add to free list
//         if (prev) {
//             prev->next = block;
//         } else {
//             freeList = block;
//         }
//         return (void*)(block + 1);
//     }
//     // Free memory (similar to free)
//     void deallocate(void *ptr) {
//         if (!ptr) return;
//         // Get the block metadata
//         Block *block = (Block*)ptr - 1;
//         block->free = true;
//         // Optionally, release back to OS if large enough
//         if (block->size >= 4096) {
//             if (block == freeList) {
//                 freeList = block->next;
//             }
//             munmap(block, block->size + sizeof(Block));
//         }
//     }
// }

// SimpleAllocator allocator;

// void testAllocator() {
//     void* p1 = allocator.allcoate(100);
//     cout << "Allocated 100 bytes at " << p1 << endl;
    
//     void* p2 = allocator.allocate(200);
//     cout << "Allocated 200 bytes at " << p2 << endl;

//     allocator.deallocate(p1);
//     cout << "Freed first block" << endl;

//     allocator.deallocate(p2);
//     cout << "Freed second block" << endl;
// }

// int main() {
//     testAllocator();
//     return 0;
// }