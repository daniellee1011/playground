#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> sieve(int num) {
    std::vector<bool> is_prime(num + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i * i <= num; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= num; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= num; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

bool isPrime(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    for (int i = 3; i * i <= num; i++) {
        if (num % i == 0) return false;
    }

    return true;
}

std::vector<int> primeNumbers(int n1, int n2) {
    std::vector<int> primes;
    primes.reserve((n2 - n1) / 2 + 1);

    for (int i = n1; i <= n2; i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    int n1, n2;
    n1 = 12;
    n2 = 57;
    std::vector<int> primes = primeNumbers(n1, n2);

    std::cout << "Size: " << primes.size() << std::endl;
    for (int i = 0; i < primes.size(); i++) {
        std::cout << primes[i] << " ";
    } std::cout << "\n";

    primes = sieve(n2);
    for (int i = 0; i < primes.size(); i++) {
        std::cout << primes[i] << " ";
    } std::cout << "\n";

    return 0;
}
