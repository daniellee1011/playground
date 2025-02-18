#include <iostream>

class GPU {
protected:
    int cores;
public:
    GPU(int c) : cores(c) {}
    virtual void displaySpecs() { std::cout << "Cores: " << cores << std::endl; }
};

class Adreno : public GPU {
public:
    Adreno(int c) : GPU(c) {}
    void displaySpecs() override {
        std::cout << "Adreno GPU with " << cores << " cores" << std::endl;
    }
};

int main() {
    GPU *gpu = new Adreno(512);
    gpu->displaySpecs();
    delete gpu;
    return 0;
}
