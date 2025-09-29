#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5   // number of vertices in the graph

// Find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the final shortest distances
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];       // shortest distance from src to i
    bool visited[V];   // visited vertices

    // Initialize distances as infinite and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0; // distance to source is always 0

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited); // pick min distance vertex
        visited[u] = true;

        // Update dist[v] if:
        // 1. v is not visited
        // 2. there is an edge from u to v
        // 3. total weight of path through u is smaller
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist);
}

// Driver code
int main() {
    // Example graph as adjacency matrix
    int graph[V][V] = {
        {0, 4, 2, 0, 0},
        {4, 0, 1, 5, 0},
        {2, 1, 0, 8, 10},
        {0, 5, 8, 0, 2},
        {0, 0, 10, 2, 0}
    };

    dijkstra(graph, 0); // Run Dijkstra from source vertex 0
    return 0;
}

