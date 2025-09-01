#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node* link;
};
int size,count;
struct node* head=NULL;
struct node* tail=NULL;

void Enque(struct node* head1,struct node* tail1,int key){
	
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	if(head1==NULL){
		temp->data=key;
		temp->link=temp;
		head=temp;
	    tail=temp;
	    count++;
	    return ;
	}
	temp->data=key;
	temp->link=head;
	tail1->link=temp;
	tail=temp;
	count++;
}
void Deque(struct node * head1,struct node* tail1){
	if(head1==tail1){
		free(head1);
		head=NULL;
		tail=NULL;
		count=0;
		return;
	}
	struct node* temp=head1;
	head1=temp->link;
	free(temp);
	tail1->link=head1;
	head=head1;
	count--;
	
}
void print(struct node* head1){
	 struct node* temp=head1;
	 if(temp==NULL){
	 printf("Queue is empty....\n\n");
	 return ;
	 }
	 
	do{
		printf("%d  ",temp->data);
		temp=temp->link;
	}while(temp!=head1);
	printf("\n");
	
}

int main(){
	printf("Enter size of Queue\n");
	scanf("%d",&size);
   int choice,num;
   bool flag=true;
   while(flag){
     	printf("1. Enqueue  2. Dequeue  3. Traverse  4. Exit\n");
        scanf("%d",&choice);
   	  switch(choice){
   	  	case 1:
   	  		if(size==count){
		printf("Queue is full. Insertion not possible....\n\n");
		break ;
	     }
   	 	printf("Enter a number\n");
   	 	scanf("%d",&num);
   	 	Enque(head,tail,num);
   	    break;
   	 case 2:
   	 	Deque(head,tail);
   	 	break;
   	 case 3:
   	 	 print(head);
   	 	 break;
   	 case 4:
   	 	printf("Program terminated successfully ....");
   	 	flag=false;
   	 	break;
   	 
   	 default:
   	 	printf("Invalid input\n");
   	 	   	 	
		 }
   }
   return 0;
	
}
