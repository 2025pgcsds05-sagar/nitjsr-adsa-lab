#include <stdio.h>
#include <stdlib.h>

// AVL tree node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Utility function to get max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get height of node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Create new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // new node at leaf has height 1
    return node;
}

// Right rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // new root
}

// Left rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // new root
}

// Get balance factor
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert item in AVL tree
struct Node* insertItem(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else
        return node; // No duplicate keys

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // Perform rotations
    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // unchanged node
}

// Get node with minimum key (used for deletion)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete item from AVL tree
struct Node* deleteItem(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        // Node with one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                // No child
                temp = root;
                root = NULL;
            } else
                *root = *temp; // Copy contents

            free(temp);
        } else {
            // Node with two children
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Balance the tree
    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search item
struct Node* searchItem(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchItem(root->left, key);
    else
        return searchItem(root->right, key);
}

// Create an empty tree
struct Node* createTree() {
    return NULL;
}

// Delete the whole tree
void deleteTree(struct Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Preorder traversal for checking
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Driver code
int main() {
    struct Node* root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("Preorder traversal of AVL tree:\n");
    preOrder(root);

    root = deleteItem(root, 40);
    printf("\nAfter deletion of 40:\n");
    preOrder(root);

    struct Node* search = searchItem(root, 25);
    if (search != NULL)
        printf("\nFound %d\n", search->key);
    else
        printf("\nNot Found\n");

    deleteTree(root);
    return 0;
}

