#include <iostream>

template <typename T>
class SharedPtr {
private:
    T *ptr;
    int *refCount;
public:
    explicit SharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1)) {}

    // Copy constructor
    SharedPtr(const SharedPtr<T>& other) : ptr(other.ptr), refCount(other.refCount) {
        ++(*refCount);
    }

    // Copy assignment operator
    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        if (this != &other) {
            // Decrement old reference count and delete if necessary
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }
            // Copy new pointer and reference count
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
        }
        return *this;
    }

    ~SharedPtr() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};

int main() {
    SharedPtr<int> sp1(new int(42));
    {
        SharedPtr<int> sp2 = sp1;
        std::cout << *sp2 << std::endl;
    }
    std::cout << *sp1 << std::endl;
    return 0;
}