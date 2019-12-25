#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
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

int Partition(SQlist *L,int low,int high)
{
	int t,i,j,key;
	i=low;
	j=high;
	key=L->base[low];
	while(i<j)
	{
		while(i<j&&L->base[j]>=key) j--;
		L->base[i]=L->base[j];
		while(i<j&&L->base[i]<=key) i++;
		L->base[j]=L->base[i];
	}
	L->base[i]=key;
	return i;
} 

void QSort(SQlist *L,int low,int high)
{
	int key;
	if(low<high)
	{
		key=Partition(L,low,high);
		QSort(L,low,key-1);
		QSort(L,key+1,high);
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

int main()
{
	SQlist list;
	InitSq(&list);
	CreateSQ(&list);
	QSort(&list,0,list.length-1);
	output(list);
	return 0;
}
