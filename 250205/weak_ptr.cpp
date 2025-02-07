#include <iostream>
#include <memory>

class WeakExample {
public:
    WeakExample() { std::cout << "WeakExample Constructor\n"; }
    ~WeakExample() { std::cout << "WeakExample Deconsturctor\n"; }
    void show() { std::cout << "Weak Pointer Example\n"; }
};

void weakPtrExample() {
    std::shared_ptr<WeakExample> sharedPtr = std::make_shared<WeakExample>();
    std::weak_ptr<WeakExample> weakPtr = sharedPtr;
    
    if (auto sharedLock = weakPtr.lock()) {
        sharedLock->show();
        std::cout << "Reference count: " << sharedPtr.use_count() << "\n";
    } else {
        std::cout << "Object has been destroyed.\n";
    }
}

int main() {
    weakPtrExample();
    return 0;
}