#include <stdio.h>
#include <stdlib.h>

void reshapeMatrixPrint(int *matrix, int M, int N, int A, int B) {
    if (M * N != A * B) {
        printf("Invalid reshape\n");
        return;
    }

    for (int i = 0; i < A * B; i++) {
        if (i % B == 0) printf("\n");
        printf("%d ", matrix[i]);
    }
    printf("\n");
}

void reshapeMatrix(int *matrix, int M, int N, int A, int B) {
    if (M * N != A * B) {
        printf("Invalid reshape dimension\n");
        return;
    }

    int *reshaped = (int*)malloc(A * B * sizeof(int));
    for (int i = 0; i < M * N; i++) {
        reshaped[i] = matrix[i];
    }
    printf("Reshaped Matrix:\n");
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < B; j++) {
            printf("%d ", reshaped[i * B + j]);
        }
        printf("\n");
    }
    free(reshaped);
}

int main() {
    int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    reshapeMatrixPrint((int*)matrix, 3, 4, 5, 4);
    reshapeMatrixPrint((int*)matrix, 3, 4, 4, 3);

    int M = 2, N = 6;
    int matrix2[2][6] = {{1, 2, 3, 4, 5, 6}, {7, 8, 9, 10, 11, 12}};
    reshapeMatrix((int*)matrix, M, N, 3, 4);
    return 0;
}
