#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    auto greet = []() {
        std::cout << "Hello from Lambda!" << std::endl;
    };
    greet();

    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "Sum: " << add(3, 4) << std::endl;

    // Capture by Value [=]
    int x = 10;
    auto lambda_value = [=]() { std::cout << "Value of x: " << x << std::endl; };
    lambda_value();

    // Capture by Reference [&]
    auto lambda_reference = [&]() { x += 5; };
    lambda_reference();
    std::cout << "Updated x: " << x << std::endl;

    // Mixed Capture
    int y = 20;
    auto lambda_mixed = [x, &y]() { std::cout << "x (by value): " << x << ", y (by ref): " << y << std::endl; };
    lambda_mixed();

    y = 30;
    lambda_mixed();

    // Specifying Return Type
    auto divide = [](double a, double b) -> double {
        return a / b;
    };
    std::cout << "Result: " << divide(10, 2) << std::endl;

    // Using Lambdas with Standard Algorithms
    // Sorting a Vector
    std::vector<int> numbers = {4, 2, 8, 5, 1};
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;
    });
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    // Filtering with std:copy_if
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> evens;
    std::copy_if(nums.begin(), nums.end(), std::back_inserter(evens), [](int n)  {
        return n % 2 == 0;
    });
    for (int n : evens) std::cout << n << " ";
    std::cout << "\n";

    // Lambdas with std::function (Storing Lambdas)
    std::function<int(int, int)> multiply = [](int a, int b) {
        return a * b;
    };
    std::cout << "Product: " << multiply(3, 4) << std::endl;

    // Mutable Lambdas
    auto lambda = [x]() mutable {
        x += 5;
        std::cout << "Inside lambda, x: " << x << std::endl;
    };
    lambda();
    std::cout << "Outside lambda, x: " << x << std::endl;

    // Generic Lambdas (C++14+)
    auto print = [](auto x) { std::cout << x << std::endl; };
    print(10);
    print(3.14);
    print("Hello");

    return 0;
}