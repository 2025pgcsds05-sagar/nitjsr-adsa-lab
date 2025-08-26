#include<stdio.h>
void bubblesort(int a[],int n){
	int pass,i,temp,swapp=1;
	for(pass=n-1;pass>=0 && swapp;pass--){
		swapp=0;
		for(i=0;i<=pass-1;i++){
			if(a[i]>a[i+1]){
				temp=a[i];
				a[i]=a[i+1];
				a[i+1]=temp;
				swapp=1;
			}
		}
	}
}
void print(int a[],int n){
	for(int i=0;i<n;i++)
	printf("%d ",a[i]);
}
int main()
{    int size=0;
     printf("size of unsorted array\n");
     scanf("%d",&size);
	int a[size]={0};
	printf("Enter unsorted array\n");
	for(int i=0;i<size;i++)
	 scanf("%d",&a[i]);
	printf("sorted array is   ");
	bubblesort(a,size);
	print(a,size);
}
