#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int stack[MAX], top = -1;

// Push vertex to stack
void push(int v) {
    stack[++top] = v;
}

// DFS utility function
void topoDFS(int v, bool visited[], int graph[MAX][MAX], int V) {
    visited[v] = true;

    for (int i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            topoDFS(i, visited, graph, V);
        }
    }

    // Push current vertex to stack after visiting all neighbors
    push(v);
}

// Function to perform Topological Sort
void topologicalSort(int graph[MAX][MAX], int V) {
    bool visited[MAX] = {false};

    // Call DFS for all unvisited vertices
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topoDFS(i, visited, graph, V);
        }
    }

    // Print vertices in topologically sorted order
    printf("Topological Sort: ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int V = 6;
    int graph[MAX][MAX] = {0};

    // Example graph (directed)
    graph[5][2] = 1;
    graph[5][0] = 1;
    graph[4][0] = 1;
    graph[4][1] = 1;
    graph[2][3] = 1;
    graph[3][1] = 1;

    topologicalSort(graph, V);

    return 0;
}

