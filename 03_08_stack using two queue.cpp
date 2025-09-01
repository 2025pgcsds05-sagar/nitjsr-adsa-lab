#include<stdio.h>
#include<stdlib.h>
#define size 100

int q1[size], q2[size];
int front1 = -1, rear1 = -1, front2 = -1, rear2 = -1;

int isEmpty1() { return front1 == -1; }
int isEmpty2() { return front2 == -1; }

void enqueue1(int x) {
    if (rear1 == size - 1) return;
    if (front1 == -1) front1 = 0;
    q1[++rear1] = x;
}

int dequeue1() {
    if (isEmpty1()) return -1;
    int val = q1[front1];
    if (front1 == rear1) front1 = rear1 = -1;
    else front1++;
    return val;
}

void enqueue2(int x) {
    if (rear2 == size - 1) return;
    if (front2 == -1) front2 = 0;
    q2[++rear2] = x;
}

int dequeue2() {
    if (isEmpty2()) return -1;
    int val = q2[front2];
    if (front2 == rear2) front2 = rear2 = -1;
    else front2++;
    return val;
}

// Push (Enqueue costly)
void push(int x) {
    enqueue2(x);
    while (!isEmpty1()) {
        enqueue2(dequeue1());
    }
    while (!isEmpty2()) {
        enqueue1(dequeue2());
    }
}

int pop() {
    return dequeue1();
}

int main() {
    int choice,num;
    
    while(true){
    	printf("1. push  2. pop  3. Exit \n");
        scanf("%d",&choice);
    	switch(choice){
    		case 1:
    			printf("Enter a number\n");
    			scanf("%d",&num);
    			push(num);
    			break;
    		case 2:
    			printf("element popped  :%d\n",pop());
    			break;
    		case 3:
    			printf("program terminated successfully.....");
    			exit(0);
    			break;
    		default:
    			printf("Invalid Input\n");
		}
	}
}

