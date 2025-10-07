#include <stdio.h>
#include <stdbool.h>

#define MAX 100

// ----------------- SCC (Directed Graph) -----------------
int discSCC[MAX], lowSCC[MAX], stackSCC[MAX], stackMember[MAX];
int topSCC = -1, timeSCC = 0;

void SCCUtil(int u, int graph[MAX][MAX], int V) {
    discSCC[u] = lowSCC[u] = ++timeSCC;
    stackSCC[++topSCC] = u;
    stackMember[u] = 1;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (discSCC[v] == -1) {
                SCCUtil(v, graph, V);
                if (lowSCC[u] > lowSCC[v])
                    lowSCC[u] = lowSCC[v];
            } else if (stackMember[v]) {
                if (lowSCC[u] > discSCC[v])
                    lowSCC[u] = discSCC[v];
            }
        }
    }

    if (lowSCC[u] == discSCC[u]) {
        printf("SCC: ");
        while (stackSCC[topSCC] != u) {
            printf("%d ", stackSCC[topSCC]);
            stackMember[stackSCC[topSCC--]] = 0;
        }
        printf("%d\n", stackSCC[topSCC]);
        stackMember[stackSCC[topSCC--]] = 0;
    }
}

void findSCCs(int graph[MAX][MAX], int V) {
    for (int i = 0; i < V; i++) {
        discSCC[i] = -1;
        lowSCC[i] = -1;
        stackMember[i] = 0;
    }
    for (int i = 0; i < V; i++)
        if (discSCC[i] == -1)
            SCCUtil(i, graph, V);
}

// ----------------- Articulation Points & Bridges (Undirected Graph) -----------------
int discAP[MAX], lowAP[MAX], parentAP[MAX], timeAP = 0;

void APBUtil(int u, int graph[MAX][MAX], int V, bool ap[]) {
    int children = 0;
    discAP[u] = lowAP[u] = ++timeAP;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (discAP[v] == -1) {
                children++;
                parentAP[v] = u;
                APBUtil(v, graph, V, ap);
                if (lowAP[u] > lowAP[v])
                    lowAP[u] = lowAP[v];

                if ((parentAP[u] == -1 && children > 1) || (parentAP[u] != -1 && lowAP[v] >= discAP[u]))
                    ap[u] = true;

                if (lowAP[v] > discAP[u])
                    printf("Bridge: %d -- %d\n", u, v);

            } else if (v != parentAP[u]) {
                if (lowAP[u] > discAP[v])
                    lowAP[u] = discAP[v];
            }
        }
    }
}

void findAPB(int graph[MAX][MAX], int V) {
    bool ap[MAX] = {false};
    for (int i = 0; i < V; i++) {
        discAP[i] = -1;
        lowAP[i] = -1;
        parentAP[i] = -1;
    }
    for (int i = 0; i < V; i++)
        if (discAP[i] == -1)
            APBUtil(i, graph, V, ap);

    printf("Articulation Points: ");
    for (int i = 0; i < V; i++)
        if (ap[i])
            printf("%d ", i);
    printf("\n");
}

// ----------------- Biconnected Components (Undirected Graph) -----------------
typedef struct { int u, v; } Edge;
Edge edgeStack[MAX];
int topE = -1;
int discB[MAX], lowB[MAX], parentB[MAX], timeB = 0;

void pushEdge(int u, int v) { edgeStack[++topE].u = u; edgeStack[topE].v = v; }

void popEdgeUntil(int u, int v) {
    printf("BCC: ");
    while (topE >= 0) {
        Edge e = edgeStack[topE--];
        printf("(%d-%d) ", e.u, e.v);
        if (e.u == u && e.v == v) break;
    }
    printf("\n");
}

void BCCUtil(int u, int graph[MAX][MAX], int V) {
    discB[u] = lowB[u] = ++timeB;
    int children = 0;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (discB[v] == -1) {
                children++;
                parentB[v] = u;
                pushEdge(u, v);
                BCCUtil(v, graph, V);
                if (lowB[u] > lowB[v]) lowB[u] = lowB[v];

                if ((parentB[u] == -1 && children > 1) || (parentB[u] != -1 && lowB[v] >= discB[u]))
                    popEdgeUntil(u, v);

            } else if (v != parentB[u] && discB[v] < discB[u]) {
                if (lowB[u] > discB[v]) lowB[u] = discB[v];
                pushEdge(u, v);
            }
        }
    }
}

void findBCCs(int graph[MAX][MAX], int V) {
    for (int i = 0; i < V; i++) { discB[i] = -1; lowB[i] = -1; parentB[i] = -1; }
    for (int i = 0; i < V; i++)
        if (discB[i] == -1)
            BCCUtil(i, graph, V);
    if (topE >= 0) popEdgeUntil(edgeStack[topE].u, edgeStack[topE].v);
}

// ----------------- Main Function -----------------
int main() {
    int V = 5;
    int directedGraph[MAX][MAX] = {0};
    int undirectedGraph[MAX][MAX] = {0};

    // Example directed graph for SCC
    directedGraph[0][2] = 1; directedGraph[2][1] = 1; directedGraph[1][0] = 1;
    directedGraph[0][3] = 1; directedGraph[3][4] = 1;

    // Example undirected graph for AP, Bridges, BCC
    undirectedGraph[0][1] = undirectedGraph[1][0] = 1;
    undirectedGraph[1][2] = undirectedGraph[2][1] = 1;
    undirectedGraph[2][0] = undirectedGraph[0][2] = 1;
    undirectedGraph[1][3] = undirectedGraph[3][1] = 1;
    undirectedGraph[3][4] = undirectedGraph[4][3] = 1;

    printf("Strongly Connected Components (SCCs):\n");
    findSCCs(directedGraph, V);

    printf("\nArticulation Points and Bridges:\n");
    findAPB(undirectedGraph, V);

    printf("\nBiconnected Components (BCCs):\n");
    findBCCs(undirectedGraph, V);

    return 0;
}

