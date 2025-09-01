#include<stdio.h>
void insertionsort(int a[],int n){
	int i,j,temp;
	for(i=0;i<n-1;i++){
		
	   j=i+1;
	   
	   while(a[j-1]>a[j] &&j>0){
	   	temp=a[j];
	   	a[j]=a[j-1];
	   	a[j-1]=temp;
	   	j--;
	   }
	}
}
void print(int a[],int n){
	for(int i=0;i<n;i++)
	printf("%d ",a[i]);
}
int main(){
	int a[7]={-11,-75,2,5,75,3,7};
	insertionsort(a,7);
	print(a,7);
}
