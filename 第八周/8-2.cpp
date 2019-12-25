#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10

typedef struct sqlist
{
	int* base;
	int length;
	int listsize;
}SQlist;


void InitSq(SQlist *list)
{
	list->base=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!list->base) 
	{
		printf("创建顺序表失败！"); 
	    exit(0);
	}
	list->length=0;
	list->listsize=LIST_INIT_SIZE;
}
void CreateSQ(SQlist *list)
{
	int i,n;
	int *newbase;
	printf("输入n\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		if(list->length>=list->listsize)
	    {
			newbase=(int*)realloc(list->base,(list->listsize+LISTINCERMENT)*sizeof(int));
			list->base=newbase;
			list->listsize+=LISTINCERMENT;
	    }
		printf("输入数：");
		scanf("%d",list->base+i);
		list->length++;
	}
}
void visit(int e)
{
	printf("%d\t",e);
}

void output(SQlist list)
{
	int n=list.length;
	int i;
	for(i=0;i<n;i++)
	{
		visit(list.base[i]);
	}
}

void SwapSort(SQlist list)
{
	int i,j;
	int n,t;
	n=list.length;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(list.base[j+1]<list.base[j])
			{
				t=list.base[j+1];
				list.base[j+1]=list.base[j];
				list.base[j]=t;
			}
		}
	}
	output(list);
}

void SelectSort(SQlist list)
{
	int i,j;
	int t;
	int min;
	int flag=0;
	int n=list.length;
	for(i=0;i<n;i++)
	{
		flag=i;
		min=list.base[i];
		for(j=i;j<n;j++)
		{
			if(min>list.base[j])
			{
				min=list.base[j];
				flag=j;
			}
		}
		if(flag!=i)
		{
			t=list.base[i];
			list.base[i]=list.base[flag];
			list.base[flag]=t;
		}
	}
	output(list);
}

void Merge(SQlist *list,SQlist *L,int i,int m,int n)
{
	int j,k;
	int s=0;
	for(j=m+1,k=i;i<=m&&j<=n;k++)
	{
		if(list->base[i]<list->base[j]){
			L->base[k]=list->base[i];
			i++; 
		}
		else{
			L->base[k]=list->base[j];
			j++;
	    }
	}
	if(i<=m)
	{
		while(i<=m)
		{
			L->base[k]=list->base[i];
			k++;
			i++;
		}
	}
	if(j<=n)
	{
		while(j<=n)
		{
			L->base[k]=list->base[j];
			k++;
			j++;
		}
	}
}

void MSort(SQlist list,SQlist L)
{
	int m=1;
	int i,begin=0,mid=0,end=1;
	while(m<=list.length)
	{
		while(end<list.length)
		{
			Merge(&list,&L,begin,mid,end);
			begin+=2*m;
			mid=begin+m-1;
			end+=2*m;
		}
		if(end>=list.length)
		{
			Merge(&list,&L,begin,mid,list.length-1);
		}
		for(i=0;i<list.length;i++)
		{
			list.base[i]=L.base[i];
		}
		m*=2;
		begin=0;
		mid=begin+m-1;
		end=begin+2*m-1;
	}
	output(list);
}

void MergeSort(SQlist list)
{
	SQlist L;
	InitSq(&L);
	L.length=list.length;
	MSort(list,L);
}

int main()
{
	SQlist list;
	int m=1;
	while(m)
	{
		system("cls");
		printf("交换排序\n");
		printf("选择排序\n");
		printf("归并排序\n");
		printf("输入数列\n");
		scanf("%d",&m);
		switch(m)
		{
			case 1:{
				system("cls");
				SwapSort(list);
				system("pause");
				break;
			}
			case 2:{
				system("cls");
				SelectSort(list);
				system("pause"); 
				break;
			}
			case 3:{
				system("cls");
				MergeSort(list);
				system("pause");
				break;
			}
			case 4:{
				system("cls");
				InitSq(&list);
				CreateSQ(&list);
				system("pause");
				break;
			}
			case 0:{
				exit(0);
				break;
			}
		}
	}
}
