#include <iostream>
#include <cstring>

class String {
private:
    char* data;
public:
    // Constructor
    String(const char* str = "") {
        data = new char[std::strlen(str) + 1];
        std::strcpy(data, str);
    }
    // Copy constructor
    String(const String& other) {
        data = new char[std::strlen(other.data) + 1];
        std::strcpy(data, other.data);
    }
    // Copy assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            data = new char[std::strlen(other.data) + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }
    // Destructor
    ~String() {
        delete[] data;
    }

    void print() const { std::cout << data << std::endl; }
};

int main() {
    String s1("Hello");
    String s2 = s1;
    s2.print();
    String s3;
    s3 = s1;
    s3.print();
    return 0;
}