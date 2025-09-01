#include<stdio.h>
#define size 3
int arr[size];
int start=-1;
int end=-1;
int num;
void Enqueue(){
	if((end+1)%size==start){
		printf("queue is full insertion not possible....\n");
		return ;
	}
	printf("Enter a number \n");
	scanf("%d",&num);
	if(start==-1)
	 start=0;
	 end=(end+1)%size;
	 arr[end]=num;	
}
void Dequeue(){
	if(start==-1){
		printf("queue is empty....");
		return ;
	}
	if(start==end){
		start=-1;
	    end=-1;
	    return;
	}
	start=(start+1)%size;
}
void print(){
	if(start==-1){
		printf("Queue is empty....\n");
	    return ;
	}
	
	for(num=start;num<=end;){
		printf("%d ",arr[num]);
		num=(num+1)%size;
	}
	printf("\n");
}
int main(){
	int choice;
	bool flag=true;
	
	
	while(flag){
		printf("1. Enqueue 2. Dequeue 3. Traverse 4.  Exit\n");
		scanf("%d",&choice);
	switch(choice){
		
		case 1:
			Enqueue();
			break;
		case 2:
			Dequeue();
			break;
		case 3:
			print();
			break;
		case 4:
			printf("Program terminated successfully....\n");
			flag=false;
			break;
		default:
			printf("Invalid input\n");
	}
}
	return 0;
}
