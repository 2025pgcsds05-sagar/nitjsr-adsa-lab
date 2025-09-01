#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
int stack1[maxsize];
int stack2[maxsize];
int size=0;//total element in queue
int head;//index of first element of queue

//method 1
void Enqueue1(int key){ //making Enqueue operation costly 
    if(size==maxsize){
    	printf("queue is full ....\n");
    	return ;
	}
	int i=0;
	
	for(i=0;i<size;i++)  //move 1st stack to 2nd stack
		stack2[i]=stack1[(size-i-1)];

	
	stack1[0]=key;//add new element to 1st stack
	size=size+1;
	
	for(i=1;i<size+1;i++)//move element from 2nd stack to 1st stack again
	stack1[i]=stack2[(size-i-1)];
	head=size-1;
	
}
void Dequeue1(){ 
    if(head<0){
    	printf("queue is empty....\n");
    	return;
	}
    printf("Element %d removed from Queue\n",stack1[head]);
	head=head-1;
}

//method 2
void Enqueue2(int key){
	if(size==maxsize){
		printf("queue is full....\n");
		return ;
	}
	stack1[size]=key;
	size=size+1;

}
void Dequeue2(){//making pop operation costly
	if(size<1){
		printf("Queue is empty...\n");
		return ;
	}
	int i;
	for(i=size-1;i>0;i--)
	 stack2[size-i-1]=stack1[i];
	printf("Element %d removed\n",stack1[0]);
	size=size-1;
	for(i=size;i>=0;i--){
		stack1[size-i-1]=stack2[i];
	}
}

void print(){
	
	int i=size;
	for(i=0;i<size;i++)
	printf("%d ",stack1[i]);
}
int main(){
	int var,choice,num;
    bool flag=true;
    printf("1. Make enqueue operation costly    2. Make pop operation  costly\n");
    scanf("%d",&var);
    switch(var){
    	case 1:
    		while(flag){
    			printf("1. Enqueue 2. Dequeue 3. Exit\n");
    			scanf("%d",&choice);
    			switch(choice){
    				case 1:
    				printf("enter a numeber \n");
    				scanf("%d",&num);
    				Enqueue1(num);
    				break;
    			case 2:
    				Dequeue1();
    				break;
    			case 3:
    				exit(0);
				}
    	    }
    	case 2:
    	    	while(flag){
    			printf("1. Enqueue 2. Dequeue 3. Exit\n");
    			scanf("%d",&choice);
    			switch(choice){
    				case 1:
    				printf("enter a numeber \n");
    				scanf("%d",&num);
    				Enqueue2(num);
    				break;
    			case 2:
    				Dequeue2();
    				break;
    			case 3:
    				exit(0);
				}
    	    }
    	default:
    		printf("Invalid input.....\n");
	}

}
