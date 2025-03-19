#include <iostream>
#include <vector>

using namespace std;

std::vector<int> sieve(int n2) {
    std::vector<bool> is_prime(n2 + 1, true);
    // 10
    // 1 2 3 4 5 6 7 8 9 10
    // t t t t t t t t t t
    // f t t f t f t f f f
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n2; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n2; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= n2; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

// Functions to get prime numbers within a range '[n1, n2]'
std::vector<int> primeNumbers(int n1, int n2) {
    std::vector<int> all_primes = sieve(n2);
    std::vector<int> primes_in_range;

    for (int &prime : all_primes) {
        if (prime >= n1) primes_in_range.push_back(prime);
    }

    return primes_in_range;
}

int main() {
    int n1 = 12, n2 = 57;
    std::vector<int> primes = primeNumbers(n1, n2);
    std::cout << "size: " << primes.size() << endl;
    for (int &prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << "\n";
    return 0;
}