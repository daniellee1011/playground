#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Compare {
    bool operator()(string s1, string s2) {
        return s1 > s2;
    }
};

struct ComparePair {
    bool operator()(pair<int, string> &p1, pair<int, string> &p2) {
        if (p1.first == p2.first) {
            return p1.second > p2.second;
        }
        return p1.first > p2.first;
    }
};

int main() {
    vector<string> vec = {"bcd", "efg", "bca", "abc"};
    for (string& s : vec) {
        cout << s << " ";
    } cout << "\n";

    cout << "*** Sorted" << "\n";
    sort(vec.begin(), vec.end());
    for (string& s : vec) {
        cout << s << " ";
    } cout << "\n";

    cout << "** Custom sorted" << "\n";
    sort(vec.begin(), vec.end(), Compare());
    for (string& s: vec) {
        cout << s << " ";
    } cout << "\n";

    cout << "*** Original pair" << endl;
    vector<pair<int, string>> vec2 = {{2, "abc"}, {2, "bca"}, {1, "dec"}, {4, "acd"}, {4, "z"}};
    for (auto& pair : vec2) {
        cout << pair.first << ": " << pair.second << endl;
    } cout << "\n";

    sort(vec2.begin(), vec2.end(), ComparePair());
    cout << "*** Sorted" << endl;
    for (auto& pair : vec2) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}