#include <stdio.h>

void swap(int arr[], int start, int end) {
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
}

int partition(int arr[], int start, int end) {
    int mid = (start + end) / 2;
    int pivot = arr[mid];
    while (start <= end) {
        while (arr[start] < pivot) start++;
        while (arr[end] > pivot) end--;
        if (start <= end) {
            swap(arr, start, end);
            start++;
            end--;
        }
    }
    return start;
}

void quickSort(int arr[], int start, int end) {
    int part2 = partition(arr, start, end);
    
    if (start < part2 - 1) {
        quickSort(arr, start, part2 - 1);
    }
    if (part2 < end) {
        quickSort(arr, part2, end);
    }
}

int main() {
    int arr[] = {5, 0, 3, 1, 7, 4, 9, 6, 2, 8};
    quickSort(arr, 0, sizeof(arr)/ sizeof(int) - 1);
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int arr2[] = {3, 3, 3, 3, 3, 3, 3};
    quickSort(arr2, 0, 6);
    for (int i = 0; i < 7; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    return 0;
}
