#include <iostream>
#include <cmath>

int num = 6;
const int INF = 1e9;

int arr[6][6] = {
    {0, 2, 5, 1, INF, INF},
    {2, 0, 3, 2, INF, INF},
    {5, 3, 0, 3, 1, 5},
    {1, 2, 3, 0, 1, INF},
    {INF, INF, 1, 1, 0, 2},
    {INF, INF, 5, INF, 2, 0},
};

bool visited[6];
int dist[6];

int getSmallIndex() {
    int index = -1;
    int min = INF;
    for (int i = 0; i < num; i++) {
        if (dist[i] < min && !visited[i]) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start) {
    for (int i = 0; i < num; i++) {
        dist[i] = arr[start][i];
    }

    visited[start] = true;

    for (int i = 0; i < num - 1; i++) {
        int cur = getSmallIndex();
        visited[cur] = true;
        for (int j = 0; j < num; j++) {
            if (!visited[j]) {
                if (dist[cur] + arr[cur][j] < dist[j]) {
                    dist[j] = dist[cur] + arr[cur][j];
                }
            }
        }
    }
}

int main() {
    dijkstra(0);
    for (int i = 0; i < num; i++) {
        std::cout << dist[i] << " ";
    } std::cout << "\n";

    return 0;
}
