#include <stdio.h>
#include <stdlib.h>

#define MAX 3   // order (max number of keys in a node)

typedef struct BPTreeNode {
    int keys[MAX];
    struct BPTreeNode *child[MAX + 1];
    int isLeaf;
    int n; // number of keys
    struct BPTreeNode *next; // next leaf (for linked list)
} BPTreeNode;

BPTreeNode* root = NULL;

// Create new node
BPTreeNode* createNode(int isLeaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->isLeaf = isLeaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i < MAX + 1; i++)
        node->child[i] = NULL;
    return node;
}

// Search in B+ Tree
BPTreeNode* search(int key) {
    BPTreeNode* cur = root;
    while (cur && !cur->isLeaf) {
        int i = 0;
        while (i < cur->n && key >= cur->keys[i]) i++;
        cur = cur->child[i];
    }
    return cur;
}

// Insert into leaf node
void insertLeaf(BPTreeNode* leaf, int key) {
    int i = leaf->n - 1;
    while (i >= 0 && key < leaf->keys[i]) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    leaf->keys[i + 1] = key;
    leaf->n++;
}

// Split leaf node
BPTreeNode* splitLeaf(BPTreeNode* leaf) {
    int mid = (MAX + 1) / 2;
    BPTreeNode* newLeaf = createNode(1);

    newLeaf->n = leaf->n - mid;
    for (int i = 0; i < newLeaf->n; i++) {
        newLeaf->keys[i] = leaf->keys[mid + i];
    }

    leaf->n = mid;

    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    return newLeaf;
}

// Insert into internal node
void insertInternal(int key, BPTreeNode* parent, BPTreeNode* child) {
    int i = parent->n - 1;
    while (i >= 0 && key < parent->keys[i]) {
        parent->keys[i + 1] = parent->keys[i];
        parent->child[i + 2] = parent->child[i + 1];
        i--;
    }
    parent->keys[i + 1] = key;
    parent->child[i + 2] = child;
    parent->n++;
}

// Split internal node
BPTreeNode* splitInternal(BPTreeNode* node, int* upKey) {
    int mid = node->n / 2;
    BPTreeNode* newInternal = createNode(0);

    *upKey = node->keys[mid];

    newInternal->n = node->n - mid - 1;
    for (int i = 0; i < newInternal->n; i++) {
        newInternal->keys[i] = node->keys[mid + 1 + i];
    }
    for (int i = 0; i <= newInternal->n; i++) {
        newInternal->child[i] = node->child[mid + 1 + i];
    }

    node->n = mid;
    return newInternal;
}

// Insert in B+ Tree
void insert(int key) {
    if (!root) {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return;
    }

    BPTreeNode* cur = root;
    BPTreeNode* parent = NULL;

    // Go down to leaf
    while (!cur->isLeaf) {
        parent = cur;
        int i = 0;
        while (i < cur->n && key >= cur->keys[i]) i++;
        cur = cur->child[i];
    }

    insertLeaf(cur, key);

    if (cur->n == MAX) {
        BPTreeNode* newLeaf = splitLeaf(cur);
        int newKey = newLeaf->keys[0];

        if (!parent) {
            root = createNode(0);
            root->keys[0] = newKey;
            root->child[0] = cur;
            root->child[1] = newLeaf;
            root->n = 1;
        } else {
            insertInternal(newKey, parent, newLeaf);

            // Split internal if overflow
            while (parent->n == MAX) {
                int upKey;
                BPTreeNode* newInternal = splitInternal(parent, &upKey);

                if (parent == root) {
                    root = createNode(0);
                    root->keys[0] = upKey;
                    root->child[0] = parent;
                    root->child[1] = newInternal;
                    root->n = 1;
                    break;
                }
            }
        }
    }
}

// Traverse leaves
void traverse() {
    if (!root) {
        printf("Tree is empty\n");
        return;
    }
    BPTreeNode* cur = root;
    while (!cur->isLeaf) cur = cur->child[0]; // go to leftmost leaf
    while (cur) {
        for (int i = 0; i < cur->n; i++) printf("%d ", cur->keys[i]);
        cur = cur->next;
    }
    printf("\n");
}

// Delete entire tree
void deleteTree(BPTreeNode* node) {
    if (!node) return;
    if (!node->isLeaf) {
        for (int i = 0; i <= node->n; i++) deleteTree(node->child[i]);
    }
    free(node);
}

int main() {
    insert(10);
    insert(20);
    insert(5);
    insert(6);
    insert(12);
    insert(30);
    insert(7);
    insert(17);

    printf("Traversal of B+ Tree: ");
    traverse();

    BPTreeNode* res = search(6);
    if (res) printf("Found 6 in leaf\n");
    else printf("6 not found\n");

    deleteTree(root);
    root = NULL;
    printf("Tree deleted.\n");
    return 0;
}

