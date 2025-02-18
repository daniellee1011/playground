#include <iostream>

class GPU {
public:
    static int maxClockSpeed() {
        return 1500;
    }
};

int main() {
    std::cout << "Max GPU Clock speed: " << GPU::maxClockSpeed() << " MHz\n";
    return 0;
}
