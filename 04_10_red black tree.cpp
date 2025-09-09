#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

typedef struct Node {
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;
Node *NIL = NULL;   // Sentinel NIL node (all leaves)

// Utility function to create a new node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;   // New nodes are red
    node->left = node->right = node->parent = NIL;
    return node;
}

// Left rotation
void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right rotation
void rightRotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix violation after insertion
void insertFixup(Node **root, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right; // uncle
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left; // uncle
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert a node
void insert(Node **root, int data) {
    Node *z = createNode(data);
    Node *y = NIL;
    Node *x = *root;

    while (x != NIL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if (y == NIL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    z->left = z->right = NIL;
    z->color = RED;

    insertFixup(root, z);
}

// Tree minimum
Node* minimum(Node *node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

// Fix violation after deletion
void deleteFixup(Node **root, Node *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Delete a node
void deleteNode(Node **root, int data) {
    Node *z = *root;
    while (z != NIL && z->data != data) {
        if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (z == NIL) {
        printf("Node %d not found\n", data);
        return;
    }

    Node *y = z;
    Node *x;
    enum Color yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        if (z->parent == NIL)
            *root = z->right;
        else if (z == z->parent->left)
            z->parent->left = z->right;
        else
            z->parent->right = z->right;
        x->parent = z->parent;
    } else if (z->right == NIL) {
        x = z->left;
        if (z->parent == NIL)
            *root = z->left;
        else if (z == z->parent->left)
            z->parent->left = z->left;
        else
            z->parent->right = z->left;
        x->parent = z->parent;
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            if (y->parent != NIL)
                y->parent->left = y->right;
            if (y->right != NIL)
                y->right->parent = y->parent;
            y->right = z->right;
            z->right->parent = y;
        }
        if (z->parent == NIL)
            *root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->parent = z->parent;
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (yOriginalColor == BLACK)
        deleteFixup(root, x);
}

// Search node
Node* search(Node *root, int key) {
    while (root != NIL && key != root->data) {
        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

// Inorder traversal
void inorder(Node *root) {
    if (root != NIL) {
        inorder(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorder(root->right);
    }
}

// Delete whole tree
void deleteTree(Node *root) {
    if (root != NIL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

int main() {
    // Initialize NIL node
    NIL = (Node*)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;

    root = NIL;

    // Insert
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);

    printf("Inorder after insertions: ");
    inorder(root); printf("\n");

    // Search
    int key = 15;
    Node *found = search(root, key);
    if (found != NIL)
        printf("Node %d found\n", key);
    else
        printf("Node %d not found\n", key);

    // Delete
    deleteNode(&root, 20);
    printf("Inorder after deleting 20: ");
    inorder(root); printf("\n");

    // Delete entire tree
    deleteTree(root);
    root = NIL;
    printf("Tree deleted.\n");

    return 0;
}

