#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define Maxsize 20000

void output(int a[],int n)
{
	int max=0;
	int i=0,j,flag=-1;
	while(i<n)
	{
		for(j=0;j<n;j++)
		{
			if(max<a[j]){
				flag=j;
				max=a[j];
			}
		}
		if(flag!=-1) {
			printf("%d %d\n",flag+1,max);
			a[flag]=-1;
		}
		max=0;
		flag=-1;
		i++;
	}
}

int main()
{
	int a[Maxsize]={0};
	int b[Maxsize]={-1};
	int n,m=0;
	int flag=b[0];
	scanf("%d",&n);
	int i=0;
	for(i=0;i<n;i++)
	{
		scanf("%d",&b[i]);
		a[b[i]-1]++;
	}
	for(i=0;i<n;i++)
	{
		if(b[i]>flag) flag=b[i];
	}
	output(a,flag);
	return 0;
}
