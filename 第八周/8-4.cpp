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

void HeapAdjust(SQlist *list,int s,int m)
{
	int flag;
	flag=list->base[s-1];
	int j;
	for(j=2*s;j-1<m;j*=2)
	{
		if(j<m&&list->base[j-1]>list->base[j]) j++;
		if(flag<=list->base[j-1]) break;
		list->base[s-1]=list->base[j-1];
		s=j;
	}
	list->base[s-1]=flag;
}

void HeapSort(SQlist *list)
{
	int i;
	int t;
	for(i=list->length/2;i>0;i--)
	{
		HeapAdjust(list,i,list->length);
	}
	for(i=list->length-1;i>0;i--)
	{
		visit(list->base[0]);
		t=list->base[i];
		list->base[i]=list->base[0];
		list->base[0]=t;
		HeapAdjust(list,1,i-1);
	}
	visit(list->base[0]);
}

int main()
{
	SQlist L;
	InitSq(&L);
	CreateSQ(&L);
	HeapSort(&L);
	return 0;
}





