#include<stdio.h>
void selectionsort(int a[],int n){
	int i,j,temp;
	for(i=0;i<n-1;i++){
		
		for(j=i+1;j<n;j++){
			
			if(a[i]>a[j]){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
}
void print(int a[],int n){
	for(int i=0;i<n;i++)
	printf("%d ",a[i]);
}
int main()
{
	int a[8]={33,35,33,67,1,6,23,9};
	selectionsort(a,8);
	print(a,8);
}
