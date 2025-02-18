#include <iostream>

#define ADD(x, y) ((x) + (y))

int add(int a, int b) {
    return a + b;
}

struct Struct {
    int data;
    int (*add_func)(int, int);
};

typedef struct TypeStruct {
    int num;
    char ch;
};

class A {
    char c;
    int x;
    virtual void display() {}
};

int main() {
    std::cout << "Size of class A: " << sizeof(A) << " bytes\n";

    std::cout << "Size of struct Struct: " << sizeof(Struct) << " bytes\n";

    Struct s;
    s.data = 5;
    s.add_func = add;
    
    std::cout << "Size of struct Struct: " << sizeof(Struct) << " bytes\n";

    std::cout << "size of TypeStruct: " << sizeof(TypeStruct) << " bytes\n";
    return 0;
}
