// FizzBuzz is a classic programming challenge often used in coding interviews and as an exercise for beginners. The problem typically asks you to iterate through a range of numbers (usually 1 to n) and print each number, but with a twist:

// For numbers divisible by 3, print "Fizz" instead of the number.
// For numbers divisible by 5, print "Buzz" instead of the number.
// For numbers divisible by both 3 and 5, print "FizzBuzz".

#include <iostream>
#include <cstring>

using namespace std;

class FizzBuzz {
public:
    void solution(int n) {
        for (int i = 1; i <= n; i++) {
            if ((i % 15) == 0) {
                cout << i << ": FizzBuzz" << endl;
            } else if((i % 5) == 0) {
                cout << i << ": Bizz" << endl;
            } else if((i % 3) == 0) {
                cout << i << ": Fizz" << endl;
            } else {
                cout << i << endl;
            }
        }
    }
};

int main() {
    FizzBuzz fb;
    fb.solution(20);
    return 0;
}