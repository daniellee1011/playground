#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        int romanToInt(string s) {
            int result = 0;
    
            unordered_map<char, int> um;
            um['I'] = 1;
            um['V'] = 5;
            um['X'] = 10;
            um['L'] = 50;
            um['C'] = 100;
            um['D'] = 500;
            um['M'] = 1000;
    
            int i = 0;
            int temp = 0;
            while (i < s.length() - 1) {
                char c = s.at(i);
                char d = s.at(i + 1);
                if (um[c] == um[d]) {
                    temp += um[c];
                } else if (um[c] < um[d]) {
                    result -= temp + um[c];
                    temp = 0;
                } else {
                    result += temp + um[c];
                    temp = 0;
                }
                i++;
            }
            
            return result + um[s.back()] + temp;
        }
    };

int main() {
    return 0;
}
