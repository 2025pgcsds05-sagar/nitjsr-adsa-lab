#include <stdio.h>
#include <ctype.h>   

#define SIZE 200   

char stack[SIZE];   
int top = -1;

void push(char symbol) {
    if (top < SIZE - 1) {
        stack[++top] = symbol;
    }
}


char pop() {
    if (top == -1) return -1;
    return stack[top--];
}


char peek() {
    if (top == -1) return -1;
    return stack[top];
}

int priority(char stack) {
    if (stack == '/' || stack == '*') return 2;
    if (stack == '+' || stack == '-') return 1;
    return 0;
}

int parentheses(char expr[]) {
    int temp = 0; // counter method instead of 
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') temp++;
        else if (expr[i] == ')') {
            if (temp == 0) return 0;
            temp--;
        }
    }
    return (temp == 0);
}

void postfix(char infix[]) {
    char *ptr = infix;
    char popped;

    printf("Postfix Expression: ");
    while (*ptr != '\0') {
        if (isalnum(*ptr)) {  
            printf("%c ", *ptr);    // stackerands directly printed
        } 
        else if (*ptr == '(') {
            push(*ptr);
        } 
        else if (*ptr == ')') {
            while ((popped = pop()) != '(') {
                printf("%c ", popped);
            }
        } 
        else {  // stackerator
            while (priority(peek()) >= priority(*ptr)) {
                printf("%c ", pop());
            }
            push(*ptr);
        }
        ptr++;
    }

    while (top != -1) {
        printf("%c ", pop());
    }
    printf("\n");
}

int main() {
    char input[SIZE];
    printf("Enter an infix expression: ");
    scanf("%s", input);

    postfix(input);
    return 0;
}

