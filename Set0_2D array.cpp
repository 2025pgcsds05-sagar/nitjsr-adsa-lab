#include<stdio.h>
#include<stdlib.h>

int main(){
	int rows=0;
	int col=0;
	int i,j;
printf("Enter no of rows\n");
scanf("%d",&rows);
printf("Enter no of column\n");
scanf("%d",&col);
int array[rows][col]={0};
printf("Enter number row wise\n");
   for(i=0;i<rows;i++){
   	for(j=0;j<col;j++){
   		scanf("%d",&array[i][j]);
	   }
   }
   for(i=0;i<rows;i++){
   	for(j=0;j<col;j++){
   		printf(" %d   ",array[i][j]);
	   }
	   printf("\n");
   }
   return 0;
}
 
   
    
  



