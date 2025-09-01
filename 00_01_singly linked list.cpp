#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node* link;
};

struct node* add(struct node* ptr, int key, int pos){
	struct node *head=ptr;
	struct node* bptr=ptr;
	struct node* temp=(struct node*)malloc(sizeof (struct node));
	temp->data=key;
	temp->link=NULL;

	if (ptr==NULL)
	 return temp;
	 
	if (pos==1){
		temp->link=ptr;
		return temp;
	}
	
	while(pos!=2 && bptr->link!=NULL){
		bptr=bptr->link;
		
	}
	   temp->link=bptr->link;
	   bptr->link=temp;
	   return head;
	
}
void traverse(struct node* ptr){
	
	while(ptr!=NULL){
		printf("%d --> ",ptr->data);
		ptr=ptr->link;
	}
	printf("\b\b\b\b   \n");
}
void search(struct node* ptr,int key){
	int count =1,flag=0;
	while (ptr!=NULL){
		if(ptr->data==key){
			flag=1;
			printf("Element found at index %d  \n",count);
		}
		count++;
		ptr=ptr->link;
		
	}
	if(flag==0){
		printf("Elenment not found\n");
	}
}
struct node* remove(struct node* ptr ,int key){

	struct node* prev=ptr;
	struct node* head=ptr;
	if(ptr==NULL)
	return  head;
	
	if(ptr->data==key)  {
		prev=ptr;
		ptr=ptr->link;
		free(prev);
		return ptr;
	}
	
	while(ptr->data!=key){
		if(ptr->link==NULL){
			printf("element not found \n");
			return head;
		}
		prev=ptr;
		ptr=ptr->link;
	}
	
	if(ptr->link==NULL){
		prev->link=NULL;
		free(ptr);
		return head;
	}
	else
	  prev->link=ptr->link;
	  free(ptr);
	  return head;
}

int main(){
	printf("for invalid position element will be added at last position.....\n");
	struct node* head=(struct node*)malloc(sizeof(struct node));
	head=NULL;
	bool flag=true;
	int choice,num,pos;

         while(flag){
         	printf("1. Insert element\n2. Traverse List\n3. Delete element\n4. Search\n5. Exit\n");
         	scanf("%d",&choice);
         	switch(choice){
			 
         		case 1:
         			printf("Enter Element and postion\n");
         			scanf("%d%d",&num,&pos);
         			head=add(head,num,pos);
         			break;
         		case 2:
         			printf("Traversal is \n");
         			traverse(head);
         			break;
         		case 3:
         			printf("Enter element to be remove\n");
         			scanf("%d",&num);
         			head=remove(head,num);
         			break;
         		case 4:
         			printf("Enter Element to be search\n");
         			scanf("%d",&num);
         			search(head,num);
         			break;
         		case 5:
         			 printf("Exited from program\n");
         		     flag=false;
         		     break;
         		default:
         			printf("Invalid choice\n");
         		}
         
		 }
}
