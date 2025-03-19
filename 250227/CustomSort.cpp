#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Student {
    string name;
    int age;

    bool operator<(const Student &other) const {
        return age < other.age;
    }
};

bool CompareAge(Student s1, Student s2) {
    return s1.age > s2.age;
}

int main() {
    vector<Student> students = {{"Alice", 22}, {"Bob", 20}, {"Charlie", 25}};

    sort(students.begin(), students.end());
    for (const auto &s : students) {
        cout << s.name << ": " << s.age << endl;
    }

    sort(students.begin(), students.end(), CompareAge);
    for (const auto &s : students) {
        cout << s.name << ": " << s.age << endl;
    }

    return 0;
}