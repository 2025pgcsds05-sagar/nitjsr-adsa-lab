#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n, e;

// Function to check if current vertex can be added to Hamiltonian Cycle
bool isSafe(int v, int pos) {
    // Check if this vertex is adjacent to the previous vertex in path
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if vertex already included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive utility to solve Hamiltonian Cycle problem
bool hamCycleUtil(int pos) {
    // Base case: all vertices are in path
    if (pos == n) {
        // check if there is an edge from last vertex to first vertex
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycleUtil(pos + 1))
                return true;
            path[pos] = -1; // backtrack
        }
    }
    return false;
}

// Function to solve the Hamiltonian Cycle problem
bool hamCycle() {
    // Initialize path[]
    for (int i = 0; i < n; i++)
        path[i] = -1;

    // Start at vertex 0
    path[0] = 0;

    if (hamCycleUtil(1) == false) {
        printf("No Hamiltonian Cycle exists\n");
        return false;
    }

    printf("Hamiltonian Cycle exists:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]); // to show cycle
    return true;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v) as 0-indexed vertices:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    hamCycle();
    return 0;
}

