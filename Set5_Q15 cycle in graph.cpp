#include <stdio.h>
#include <stdbool.h>

#define V 6   // number of vertices
int graph[V][V];  // adjacency matrix
bool visited[V];
int path[V];      // current path
int pathLen = 0;

int smallest = 1e9, largest = -1;

// DFS to find cycles
void dfs(int u, int start) {
    visited[u] = true;
    path[pathLen++] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                dfs(v, start);
            }
            else if (v == start && pathLen > 2) {
                // Found a cycle
                if (pathLen < smallest) smallest = pathLen;
                if (pathLen > largest) largest = pathLen;
            }
        }
    }

    visited[u] = false;
    pathLen--;
}

int main() {
    // Example graph (undirected)
    // Cycle 0-1-2-0 and 2-3-4-5-2
    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][0] = graph[0][2] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[3][4] = graph[4][3] = 1;
    graph[4][5] = graph[5][4] = 1;
    graph[5][2] = graph[2][5] = 1;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) visited[j] = false;
        pathLen = 0;
        dfs(i, i);
    }

    if (smallest == 1e9) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest cycle length = %d\n", smallest);
        printf("Largest cycle length = %d\n", largest);
    }

    return 0;
}

