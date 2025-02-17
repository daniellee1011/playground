#include <iostream>

class base_class {
public:
    virtual void show() {
        std::cout << "Function show in the base class\n";
    }
    
    void display() {
        std::cout << "Function display in the base class\n";
    }
};

class derived_class : public base_class {
public:
    void show() {
        std::cout << "Function show in the derived class\n";
    }

    void display() {
        std::cout << "Function display in the derived class\n";
    }
};

int main() {
    base_class *p;
    base_class obj1;

    p = &obj1;
    p->show();
    p->display();

    derived_class obj2;
    p = &obj2;
    p->show();
    p->display();

    return 0;
}
