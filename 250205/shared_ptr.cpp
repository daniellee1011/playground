#include <iostream>
#include <memory>

class SharedExample {
public:
    SharedExample() { std::cout << "SharedExample Constructor\n"; }
    ~SharedExample() { std::cout << "SharedExample Deconstructor\n"; }
    void show() { std::cout << "Shared Pointer Example\n"; }
};

void sharedPtrExample() {
    std::shared_ptr<SharedExample> ptr1 = std::make_shared<SharedExample>();
    std::cout << "Reference count: " << ptr1.use_count() << "\n";

    {
        std::shared_ptr<SharedExample> ptr2 = ptr1; // Shared ownership
        ptr2->show();
        std::cout << "Reference count inside block: " << ptr1.use_count() << "\n";
    } // ptr2 goes out of scope, reference count decreases

    std::cout << "Reference count after block: " << ptr1.use_count() << "\n";
}

int main() {
    sharedPtrExample();
    return 0;
}