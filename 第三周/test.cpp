#include<stdio.h>
int fun(int a[])
{
	int i=0;
	for(i=0;i<5;i++)
	{
		a[i]=i;
	}
} 
int main()
{
	int i;
	int a[5]={0};
	fun(a);
	for(i=0;i<5;i++)
	{
		printf("%d",a[i]);
	}
	return 0;
}
