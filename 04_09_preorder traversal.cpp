//preorder traveral for binary trees without recursion
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* arr[100]; // stack
int top = -1;

// Push node to stack
void push(struct node* temp) {
    arr[++top] = temp;
}

// Pop node from stack
struct node* pop() {
    return arr[top--];
}

int isEmpty() {
    return top == -1;
}

// Create new node
struct node* newNode(int key) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert into BST
void add(struct node* root, int key) {
    struct node* temp = newNode(key);
    struct node* ptr = root;

    while (1) {
        if (key < ptr->data) {
            if (ptr->left == NULL) {
                ptr->left = temp;
                break;
            }
            ptr = ptr->left;
        } else {
            if (ptr->right == NULL) {
                ptr->right = temp;
                break;
            }
            ptr = ptr->right;
        }
    }
}

// Iterative Preorder Traversal
void preorder(struct node* root) {
    if (root == NULL) return;

    push(root);

    while (!isEmpty()) {
        struct node* curr = pop();
        printf("%d ", curr->data);

        // Push right first so left is processed first
        if (curr->right) push(curr->right);
        if (curr->left) push(curr->left);
    }
}

// Iterative Inorder Traversal

int main() {
    int n, val;
    printf("Number of elements in binary tree: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    scanf("%d", &val);
    struct node* root = newNode(val);

    for (int i = 1; i < n; i++) {
        scanf("%d", &val);
        add(root, val);
    }

    printf("Preorder Traversal  : ");
    preorder(root);
    printf("\n");

    

    return 0;
}


