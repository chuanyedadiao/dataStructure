#include<stdio.h>
#include<time.h> 
#include<stdlib.h>
#include<windows.h>
#include<math.h>

void Merge(int a[],int b[],int l,int m,int h)
{
	int i,j,t;
	i=l;
	j=m;
	t=0;
	while(i<=m-1&&j<=l)
	{
		if(a[i]<=a[j])
		{
			b[t++]=a[i++];
		}
		else
		{
			b[t++]=a[j++];
		}
	}
	while(i<=m-1)
	{
		b[t++]=a[i++];
	}
	while(j<=l)
	{
		b[t++]=a[j++];
	}
}

void Merge_sort(int a[],int b[],int n)
{
	int i,j,k,t;
	for(k=2;k<n;k=k*2)
	{
		for(i=0;(i+k)<n;i=i+k)
		{
			t=(2*i+k)/2;
			Merge(a,b,i,t,i+k-1);
		}
		Merge(a,b,i,(i+n)/2,n-1);
		for(j=0;j<n;j++)
		{
			a[j]=b[j];
		}
	}
	Merge(a,b,0,k/2,n-1);
	for(j=0;j<n;j++)
	{
		a[j]=b[j];
	}
}

void Output(int a[])
{
	int i=0;
	for(i=0;i<20;i++)
	{
		printf("%d ",a[i]);
		if((i+1)%20==0) printf("\n");
	}
} 

int main()
{   
    double m;
    int a[20]={52,14,49,53,6,74,10,25,64,91,87,10,23,54,100,56,97,14,51,20};
    int b[20];
	Merge_sort(a,b,20);
    Output(a);
	return 0;
} 
