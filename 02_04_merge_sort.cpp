#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct node {
    int l, r, state;
};

int top = -1;
struct node stack[MAX];

void push(int l, int r, int state) {
    stack[++top].l = l;
    stack[top].r = r;
    stack[top].state = state;
}

struct node pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int n) {
    push(0, n - 1, 0);
    while (!isEmpty()) {
        struct node cur = pop();
        int l = cur.l, r = cur.r, state = cur.state;
        if (l >= r) continue;
        int m = (l + r) / 2;
        if (state == 0) {
            push(l, r, 1);
            push(l, m, 0);
        } else if (state == 1) {
            push(l, r, 2);
            push(m + 1, r, 0);
        } else {
            merge(arr, l, m, r);
        }
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}

