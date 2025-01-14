#include <stdio.h>

int binary_search(int arr[], int size, int target);

int main () {
    int arr[] = {1, 3, 4, 5, 7, 10, 15};
    int size = sizeof(arr) / sizeof(int);
    int target1 = 10;
    int target2 = 6;

    printf("target1 index: %d\n", binary_search(arr, size, target1));
    printf("target2 index: %d\n", binary_search(arr, size, target2));

    return 0;
}

int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}