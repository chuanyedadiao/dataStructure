#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10 
typedef struct List{
	int *elem;
	int length;
	int listsize;
}Sqlist;
void InitList(Sqlist *list)
{
	list->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!list->elem) 
	{
		printf("创建顺序表失败！\n"); 
	    exit(0);
	}
	list->length=0;
	list->listsize=LIST_INIT_SIZE;
	printf("创建顺序表成功！\n");
}
void Insert_Sort(Sqlist *list,int m)
{
	int *p;
	int *newbase;
	p=list->elem;
	int i,j;
	for(i=0;i<list->length;i++)
	{
		if(m<*(list->elem+i)) break;
	}//找到适合的位置 
	for(j=list->length;j>i;j--)
	{
		*(list->elem+j)=*(list->elem+j-1);
	}//向后移 
    *(list->elem+i)=m;
}
void createList(Sqlist *list,int n)
{
	int i;
	int *newbase;
	for(i=0;i<n;i++)
	{
		if(list->length>=list->listsize)
	{
		newbase=(int*)realloc(list->elem,(list->listsize+LISTINCERMENT)*sizeof(int));
		list->elem=newbase;
		list->listsize+=LISTINCERMENT;
	}
		printf("输入数：");
		scanf("%d",list->elem+i);
		list->length++;
		Insert_Sort(list,*(list->elem+i));//每输入一个数进行插入排序 
	}
}
void visit(int *p)
{
	printf("%d\t",*p);
}
void ListTraverse(Sqlist p)
{
	int i=0;
	for(;i<p.length;i++)
	{
		visit(p.elem+i);
	}
}
int main()
{
	Sqlist L;
	InitList(&L);
	int n;
	printf("输入你想放入的值的个数：");
	scanf("%d",&n);
	createList(&L,n);
	printf("插入排序后的遍历\n");
	ListTraverse(L);
	return 0;
}
