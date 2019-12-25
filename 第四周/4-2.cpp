#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
int Flag(int flag[],int e)
{
	int i=0;
	while(flag[i]!=-1)
	{
		if(e==flag[i]) return 1;
		i++;
	}
	return 0;
}
int ToTal(int a[],int flag[],int n)
{
	int total=0;
	int i,j,k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[j]-a[i]==1){
				if(Flag(flag,a[i])){
					continue;
				}
				flag[k]=a[i];
				k++;
				total++;
			}
		}
	}
	return total;
}
int main()
{
	int n;
	int total;
	int a[10000],low[10000];
	printf("Please input n\n");
	scanf("%d",&n); 
	int i,ele;
	printf("Please input data\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		low[i]=-1;
	}
    total=ToTal(a,low,n);
    printf("\n%d\n",total);
    return 0;
} 
