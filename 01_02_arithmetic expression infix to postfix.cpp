#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
int top = -1;

int val_stack[MAX];
int val_top = -1;

void push(char c) {
    if (top < MAX - 1) stack[++top] = c;
}

char pop() {
    if (top == -1) return -1;
    return stack[top--];
}

char peek() {
    if (top == -1) return -1;
    return stack[top];
}

void push_val(int v) {
    if (val_top < MAX - 1) val_stack[++val_top] = v;
}

int pop_val() {
    if (val_top == -1) return -1;
    return val_stack[val_top--];
}

int precedence(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void infix_to_postfix(char infix[], char postfix[]) {
    char *e = infix;
    char x;
    int k = 0;

    while (*e != '\0') {
        if (isalnum(*e)) {
            postfix[k++] = *e;
        } else if (*e == '(') {
            push(*e);
        } else if (*e == ')') {
            while ((x = pop()) != '(') {
                postfix[k++] = x;
            }
        } else {
            while (precedence(peek()) >= precedence(*e)) {
                postfix[k++] = pop();
            }
            push(*e);
        }
        e++;
    }

    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

int evaluate_postfix(char postfix[]) {
    char *e = postfix;
    int n1, n2, n3;

    while (*e != '\0') {
        if (isdigit(*e)) {
            push_val(*e - '0');  // convert char ? int
        } else {
            n1 = pop_val();
            n2 = pop_val();
            switch (*e) {
                case '+': n3 = n2 + n1; break;
                case '-': n3 = n2 - n1; break;
                case '*': n3 = n2 * n1; break;
                case '/': n3 = n2 / n1; break;
            }
            push_val(n3);
        }
        e++;
    }
    return pop_val();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infix_to_postfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}

