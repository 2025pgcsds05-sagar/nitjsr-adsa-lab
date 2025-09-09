#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3   // Minimum degree (t). Each node can have [t-1 .. 2t-1] keys.

typedef struct BTreeNode {
    int *keys;              // Array of keys
    int t;                  // Minimum degree
    struct BTreeNode **C;   // Child pointers
    int n;                  // Current number of keys
    int leaf;               // Is true when node is leaf
} BTreeNode;

BTreeNode* createNode(int t, int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc(sizeof(int) * (2 * t - 1));
    node->C = (BTreeNode**)malloc(sizeof(BTreeNode*) * (2 * t));
    node->n = 0;
    return node;
}

// Search key in subtree rooted with this node
BTreeNode* search(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i]) i++;

    if (i < root->n && root->keys[i] == k) return root;

    if (root->leaf) return NULL;
    return search(root->C[i], k);
}

// Split child y of node x at index i
void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    int t = y->t;
    BTreeNode* z = createNode(t, y->leaf);
    z->n = t - 1;

    // Copy last (t-1) keys from y to z
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++) z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    // Create space in x for new child
    for (int j = x->n; j >= i + 1; j--) x->C[j + 1] = x->C[j];

    x->C[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[t - 1];
    x->n += 1;
}

// Insert non-full
void insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n += 1;
    } else {
        while (i >= 0 && k < x->keys[i]) i--;

        if (x->C[i + 1]->n == 2 * x->t - 1) {
            splitChild(x, i + 1, x->C[i + 1]);
            if (k > x->keys[i + 1]) i++;
        }
        insertNonFull(x->C[i + 1], k);
    }
}

// Insert key
void insert(BTreeNode** root, int k) {
    BTreeNode* r = *root;
    if (r->n == 2 * r->t - 1) {
        BTreeNode* s = createNode(r->t, 0);
        s->C[0] = r;
        *root = s;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Inorder traversal
void traverse(BTreeNode* root) {
    if (root) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf) traverse(root->C[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) traverse(root->C[i]);
    }
}

// Get predecessor
int getPred(BTreeNode* x, int idx) {
    BTreeNode* cur = x->C[idx];
    while (!cur->leaf) cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// Get successor
int getSucc(BTreeNode* x, int idx) {
    BTreeNode* cur = x->C[idx + 1];
    while (!cur->leaf) cur = cur->C[0];
    return cur->keys[0];
}

// Merge children of x at idx
void merge(BTreeNode* x, int idx) {
    int t = x->t;
    BTreeNode* child = x->C[idx];
    BTreeNode* sibling = x->C[idx + 1];

    child->keys[t - 1] = x->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < x->n; i++)
        x->keys[i - 1] = x->keys[i];
    for (int i = idx + 2; i <= x->n; i++)
        x->C[i - 1] = x->C[i];

    child->n += sibling->n + 1;
    x->n--;

    free(sibling->keys);
    free(sibling->C);
    free(sibling);
}

// Borrow from previous sibling
void borrowFromPrev(BTreeNode* x, int idx) {
    BTreeNode* child = x->C[idx];
    BTreeNode* sibling = x->C[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = x->keys[idx - 1];
    if (!child->leaf) child->C[0] = sibling->C[sibling->n];

    x->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

// Borrow from next sibling
void borrowFromNext(BTreeNode* x, int idx) {
    BTreeNode* child = x->C[idx];
    BTreeNode* sibling = x->C[idx + 1];

    child->keys[child->n] = x->keys[idx];
    if (!child->leaf) child->C[child->n + 1] = sibling->C[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// Fill child at idx if it has < t-1 keys
void fill(BTreeNode* x, int idx) {
    if (idx != 0 && x->C[idx - 1]->n >= x->t)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->C[idx + 1]->n >= x->t)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx - 1);
    }
}

// Remove key from node
void removeFromNode(BTreeNode* x, int idx) {
    int k = x->keys[idx];

    if (x->leaf) {
        for (int i = idx + 1; i < x->n; i++)
            x->keys[i - 1] = x->keys[i];
        x->n--;
    } else {
        if (x->C[idx]->n >= x->t) {
            int pred = getPred(x, idx);
            x->keys[idx] = pred;
            removeFromNode(x->C[idx], x->n);
        } else if (x->C[idx + 1]->n >= x->t) {
            int succ = getSucc(x, idx);
            x->keys[idx] = succ;
            removeFromNode(x->C[idx + 1], 0);
        } else {
            merge(x, idx);
            removeFromNode(x->C[idx], x->t - 1);
        }
    }
}

// Remove key from subtree rooted at x
void removeKey(BTreeNode* x, int k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k) idx++;

    if (idx < x->n && x->keys[idx] == k) {
        removeFromNode(x, idx);
    } else {
        if (x->leaf) {
            printf("The key %d not found\n", k);
            return;
        }
        int flag = (idx == x->n);
        if (x->C[idx]->n < x->t)
            fill(x, idx);
        if (flag && idx > x->n)
            removeKey(x->C[idx - 1], k);
        else
            removeKey(x->C[idx], k);
    }
}

// Delete node from BTree
void deleteNode(BTreeNode** root, int k) {
    if (!*root) {
        printf("The tree is empty\n");
        return;
    }
    removeKey(*root, k);
    if ((*root)->n == 0) {
        BTreeNode* tmp = *root;
        if ((*root)->leaf)
            *root = NULL;
        else
            *root = (*root)->C[0];
        free(tmp->keys);
        free(tmp->C);
        free(tmp);
    }
}

// Delete entire tree
void deleteTree(BTreeNode* root) {
    if (root) {
        if (!root->leaf) {
            for (int i = 0; i <= root->n; i++)
                deleteTree(root->C[i]);
        }
        free(root->keys);
        free(root->C);
        free(root);
    }
}

// Demo
int main() {
    BTreeNode* root = createNode(MIN_DEGREE, 1);

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("Traversal of B-Tree: ");
    traverse(root); printf("\n");

    int k = 6;
    deleteNode(&root, k);
    printf("After deleting %d: ", k);
    traverse(root); printf("\n");

    k = 13;
    deleteNode(&root, k);

    printf("Final tree: ");
    traverse(root); printf("\n");

    deleteTree(root);
    printf("Tree deleted.\n");
    return 0;
}

