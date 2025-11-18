#include <stdio.h>
#include <stdbool.h>

#define MAX 50

int graph[MAX][MAX];
int color[MAX];
int n, e;

bool isBipartiteUtil(int src) {
    int queue[MAX];
    int front = 0, rear = 0;

    color[src] = 0;  // start coloring source with 0
    queue[rear++] = src;

    while (front < rear) {
        int u = queue[front++];

        // Self-loop means not bipartite
        if (graph[u][u] == 1)
            return false;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && color[v] == -1) {
                // Assign alternate color to neighbor
                color[v] = 1 - color[u];
                queue[rear++] = v;
            } 
            else if (graph[u][v] && color[v] == color[u]) {
                // Adjacent vertices have same color ? not bipartite
                return false;
            }
        }
    }
    return true;
}

bool isBipartite() {
    // Initialize all vertices as uncolored (-1)
    for (int i = 0; i < n; i++)
        color[i] = -1;

    // Graph may be disconnected ? check all components
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!isBipartiteUtil(i))
                return false;
        }
    }
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
        graph[v][u] = 1;  // undirected
    }

    if (isBipartite())
        printf("The graph is Bipartite.\n");
    else
        printf("The graph is NOT Bipartite.\n");

    return 0;
}

