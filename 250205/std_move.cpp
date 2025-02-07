#include <iostream>
#include <vector>

class Example {
public:
    std::vector<int> data;

    // Consturctor
    Example(std::vector<int>& d) : data(d) {
        std::cout << "Copy Constructor\n";
    }

    // Move Constructor
    Example(std::vector<int>&& d) : data(std::move(d)) {
        std::cout << "Move Constructor\n";
    }
};

int main() {
    std::vector<int> v1 = { 1, 2, 3};
    std::vector<int> v2 = std::move(v1);

    std::cout << "v1 size: " << v1.size() << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;

    std::vector<int> vec = {1, 2, 3};
    Example e1(vec);
    Example e2(std::move(vec));
    std::cout << "vec size: " << vec.size() << std::endl;

    return 0;
}