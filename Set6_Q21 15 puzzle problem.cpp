#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4   // 4x4 puzzle

// Target state (goal)
int goal[N][N] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 11, 12},
    {13, 14, 15, 0}
};

// Structure to represent a puzzle state
typedef struct Node {
    int mat[N][N];
    int x, y;        // blank tile coordinates
    int cost;        // heuristic cost (Manhattan distance)
    int level;       // depth of the node
    struct Node* parent;
} Node;

// Moves for blank tile (up, down, left, right)
int row[] = { 1, -1, 0, 0 };
int col[] = { 0, 0, -1, 1 };

// Utility to print a matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Count Manhattan distance
int calculateCost(int mat[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] != 0) {
                int targetX = (mat[i][j] - 1) / N;
                int targetY = (mat[i][j] - 1) % N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return cost;
}

// Create a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*) malloc(sizeof(Node));

    // copy matrix
    memcpy(node->mat, mat, sizeof(node->mat));

    // swap blank tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;

    node->cost = calculateCost(node->mat);
    return node;
}

// Min-Heap for priority queue
typedef struct {
    Node* nodes[10000];
    int size;
} MinHeap;

void push(MinHeap* h, Node* node) {
    h->nodes[h->size] = node;
    int i = h->size++;
    while (i && (h->nodes[(i - 1) / 2]->cost + h->nodes[(i - 1) / 2]->level) >
                (h->nodes[i]->cost + h->nodes[i]->level)) {
        Node* temp = h->nodes[i];
        h->nodes[i] = h->nodes[(i - 1) / 2];
        h->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node* pop(MinHeap* h) {
    Node* root = h->nodes[0];
    h->nodes[0] = h->nodes[--h->size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < h->size &&
            (h->nodes[left]->cost + h->nodes[left]->level) <
            (h->nodes[smallest]->cost + h->nodes[smallest]->level))
            smallest = left;

        if (right < h->size &&
            (h->nodes[right]->cost + h->nodes[right]->level) <
            (h->nodes[smallest]->cost + h->nodes[smallest]->level))
            smallest = right;

        if (smallest != i) {
            Node* temp = h->nodes[i];
            h->nodes[i] = h->nodes[smallest];
            h->nodes[smallest] = temp;
            i = smallest;
        } else break;
    }
    return root;
}

// Check if solved
int isGoal(int mat[N][N]) {
    return memcmp(mat, goal, sizeof(goal)) == 0;
}

// Print path by tracing parents
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Solve puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y) {
    MinHeap h;
    h.size = 0;

    Node* root = (Node*) malloc(sizeof(Node));
    memcpy(root->mat, initial, sizeof(root->mat));
    root->x = x;
    root->y = y;
    root->level = 0;
    root->parent = NULL;
    root->cost = calculateCost(initial);

    push(&h, root);

    while (h.size) {
        Node* min = pop(&h);

        if (isGoal(min->mat)) {
            printf("Solution found in %d moves:\n\n", min->level);
            printPath(min);
            return;
        }

        // Try moving blank in all 4 directions
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                push(&h, child);
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1,  2,  3,  4},
        {5,  6,  0,  8},
        {9,  10, 7, 11},
        {13, 14, 15, 12}
    };

    // blank tile position (row=1,col=2 in example)
    int x = 1, y = 2;

    solve(initial, x, y);

    return 0;
}

