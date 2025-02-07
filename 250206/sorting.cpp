#include <iostream>
#include <algorithm>
#include <vector>

struct Student {
    std::string name;
    int grade;
};

bool compareStudents(const Student &a, const Student &b) {
    return a.grade > b.grade;
}

bool customSort(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.second < b.second;
}

int main() {
    int arr[] = {5, 2, 9, 1, 6, 5};
    int n = sizeof(arr) / sizeof(int);
    std::sort(arr, arr + n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    } std::cout << "\n";

    std::vector<int> vec = {5, 3, 8, 6, 2, 7, 4, 1};
    std::sort(vec.begin(), vec.end());
    for (int num : vec) {
        std::cout << num << " ";
    } std::cout << "\n";

    std::sort(vec.begin(), vec.end(), std::greater<int>());
    for (int num : vec) {
        std::cout << num << " ";
    } std::cout << "\n";

    std::vector<std::pair<int, int>> vec2 = {{1, 4}, {3, 2}, {5, 1}, {4, 3}};
    std::sort(vec2.begin(), vec2.end(), customSort);
    for (const auto& pair : vec2) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    } std::cout << "\n";

    std::vector<Student> students = {{"Alice", 85}, {"Bob", 92}, {"Charlie", 78}};
    std::sort(students.begin(), students.end(), compareStudents);
    for (const Student &s: students) {
        std::cout << s.name << ": " << s.grade << std::endl;
    }

    return 0;
}