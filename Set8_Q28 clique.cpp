#include <stdio.h>
#include <stdbool.h>

#define MAX 20   // reasonable limit for brute-force

int graph[MAX][MAX];
int n, e, m;
int vertices[MAX];

// Function to check if given subset of vertices form a clique
bool isClique(int subset[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (graph[subset[i]][subset[j]] == 0)
                return false;
        }
    }
    return true;
}

// Recursive function to generate combinations of vertices of size m
bool findCliqueUtil(int start, int depth) {
    if (depth == m) {
        if (isClique(vertices, m))
            return true;
        return false;
    }

    for (int i = start; i < n; i++) {
        vertices[depth] = i;
        if (findCliqueUtil(i + 1, depth + 1))
            return true;
    }
    return false;
}

bool containsClique() {
    return findCliqueUtil(0, 0);
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    printf("Enter size of clique to find (m): ");
    scanf("%d", &m);

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

    if (containsClique())
        printf("Graph contains a clique of size %d\n", m);
    else
        printf("No clique of size %d found\n", m);

    return 0;
}

