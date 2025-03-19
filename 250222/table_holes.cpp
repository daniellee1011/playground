#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int solution(int A[], int n) {
        int m = A[0];
        int M = A[0];

        for (int i = 0; i < n; i++) {
            m = min(m, A[i]);
            M = max(M, A[i]);
        }
        int avg = (m + M) / 2;
        cout << "m, avg, M: " << m << " " << avg << " " << M << "\n";
        int median = A[0];
        for (int i = 0; i < n; i++) {
            if (abs(avg - A[i]) < abs(avg - median)) {
                median = A[i];
            }
        }
        cout << "median: " << median << "\n";

        return min(median - m, M - median);
    }
};

int main() {
    Solution sol;
    int a1[] = {11, 20, 15};
    int n = sizeof(a1) / sizeof(int);
    cout << sol.solution(a1, n) << "\n";

    int a2[] = {15, 20, 9, 11};
    n = sizeof(a2) / sizeof(int);
    cout << sol.solution(a2, n) << "\n";

    int a3[] = {1, 2, 3, 4, 10};
    n = sizeof(a3) / sizeof(int);
    cout << sol.solution(a3, n) << "\n";
    
    return 0;
}