#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices

// Function to check if the current color assignment is safe
bool isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;  // Adjacent vertex has the same color
        }
    }
    return true;
}

// Recursive utility function to solve graph coloring
bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    // If all vertices are assigned a color then return true
    if (v == V)
        return true;

    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            // Recur to assign colors to rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // Backtrack
            color[v] = 0;
        }
    }

    return false;
}

// Function to solve the m Coloring problem
bool graphColoring(int graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist\n");
        return false;
    }

    // Print the solution
    printf("Solution Exists: Following are the assigned colors:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, color[i]);

    return true;
}

// Main function
int main() {
    // Example graph (adjacency matrix)
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3; // Number of colors
    graphColoring(graph, m);

    return 0;
}

