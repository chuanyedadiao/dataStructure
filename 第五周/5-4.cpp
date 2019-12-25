#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void Judge(int a[0x100][0x100],int n,int m,int x,int y,int num[0x100][0x100])
{
	int i,j,k,p;
	int count;
	int col_s=0,row_s=0; 
	for(j=0;j<m;j++)
	{
		k=j;
		count=0;
		while(a[x][k]==a[x][y]||num[x][k]==a[x][y])
		{
			count++;
			k++;
		}
		if(count>=3){
			for(p=j;p<k;p++)
			{
				a[x][p]=0;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		k=i;
		count=0;
		while(a[k][y]==a[x][y]||num[k][y]==a[x][y])
		{
			count++;
			k++;
		}
		if(count>=3){
			for(p=i;p<k;p++)
			{
				a[p][y]=0;
			}
		}
	}
}



int main()
{
	int n,m;
    scanf("%d%d",&n,&m);
    int a[0x100][0x100];
    int num[0x100][0x100];
    int i,j;
    for(i=0;i<n;i++)
    {
    	for(j=0;j<m;j++)
    	{
    	    scanf("%d",&a[i][j]);
			num[i][j]=a[i][j];	
    	}
    }//输入 
    for(i=0;i<n;i++)
    {
    	for(j=0;j<m;j++)
    	{
    		Judge(a,n,m,i,j,num);
    	}
    }
    printf("更改后:\n");
    for(i=0;i<n;i++)
    {
    	for(j=0;j<m;j++)
    	printf("%d ",a[i][j]);
    	printf("\n");
    }
    return 0;
} 
