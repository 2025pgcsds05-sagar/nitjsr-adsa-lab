#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 10  // Adjust for graph size (brute force feasible for =10 nodes)

int tsp(int graph[MAX][MAX], bool visited[MAX], int pos, int n, int count, int cost, int* ans) {
    if (count == n && graph[pos][0]) { // All cities visited, return to start
        if (cost + graph[pos][0] < *ans) {
            *ans = cost + graph[pos][0];
        }
        return *ans;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[pos][i]) {
            visited[i] = true;
            tsp(graph, visited, i, n, count + 1, cost + graph[pos][i], ans);
            visited[i] = false; // backtrack
        }
    }
    return *ans;
}

int main() {
    int n = 4; // number of nodes
    int graph[MAX][MAX] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    bool visited[MAX] = {false};
    visited[0] = true; // start from city 0
    int ans = INT_MAX;

    tsp(graph, visited, 0, n, 1, 0, &ans);

    printf("Minimum cost of TSP: %d\n", ans);
    return 0;
}

