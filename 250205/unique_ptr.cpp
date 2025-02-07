#include <iostream>
#include <memory>

class UniqueExample {
public:
    UniqueExample() { std::cout << "UnqiueExample constructor\n"; }
    ~UniqueExample() { std::cout << "UniqueExample deconstructor\n"; }
    void show() { std::cout << "Unique Pointer Example\n"; }
};

void uniquePtrExample() {
    std::unique_ptr<UniqueExample> ptr = std::make_unique<UniqueExample>();
    ptr->show();

    // Transferring ownership
    if (!ptr) {
        std::cout << "ptr is now null after move.\n";
    }
}

int main() {
    uniquePtrExample();
    return 0;
}