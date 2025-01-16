#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int grade;
};

bool compareStudentsGrade(const Student& a, const Student& b) {
    return a.grade > b.grade;
}

bool compareStudentsName(const Student& a, const Student& b) {
    return a.name > b.name;
}

int main() {
    std::vector<Student> students = {
        {"Alice", 90},
        {"Bob", 85},
        {"Charlie", 95}
    };

    std::cout << "Not Sorted" << std::endl;
    for (auto& student : students) {
        std::cout << student.name << " - " << student.grade << std::endl;
    }
    std::cout << std::endl;

    sort(students.begin(), students.end(), compareStudentsName);

    std::cout << "Sorted" << std::endl;
    for (auto& student : students) {
        std::cout << student.name << " - " << student.grade << std::endl;
    }

    return 0;
}