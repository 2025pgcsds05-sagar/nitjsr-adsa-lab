#include <stdio.h>
#include <stdlib.h>

#define V 6  // number of vertices

// Graph represented as adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adj[V];
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;
}

// States: 0 = unvisited, 1 = visiting, 2 = finished
int state[V];
int discover[V], finish[V], timeCounter = 0;

// DFS with edge classification
void DFS_visit(struct Graph* graph, int u) {
    state[u] = 1; // visiting
    discover[u] = ++timeCounter;

    struct Node* temp = graph->adj[u];
    while (temp != NULL) {
        int v = temp->vertex;
        if (state[v] == 0) {
            printf("Tree Edge: %d -> %d\n", u, v);
            DFS_visit(graph, v);
        }
        else if (state[v] == 1) {
            printf("Back Edge: %d -> %d\n", u, v);
        }
        else if (state[v] == 2) {
            if (discover[u] < discover[v])
                printf("Forward Edge: %d -> %d\n", u, v);
            else
                printf("Cross Edge: %d -> %d\n", u, v);
        }
        temp = temp->next;
    }

    state[u] = 2; // finished
    finish[u] = ++timeCounter;
}

void DFS(struct Graph* graph) {
    for (int i = 0; i < V; i++) {
        state[i] = 0;
        discover[i] = finish[i] = 0;
    }
    timeCounter = 0;

    for (int i = 0; i < V; i++) {
        if (state[i] == 0) {
            DFS_visit(graph, i);
        }
    }
}

// Driver code
int main() {
    struct Graph graph;
    for (int i = 0; i < V; i++)
        graph.adj[i] = NULL;

    // Example directed graph
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 1);  // back edge
    addEdge(&graph, 4, 5);

    DFS(&graph);

    return 0;
}

