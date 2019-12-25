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
	}
}
int TurnPoint(Sqlist *L,int n)
{
	int i=1;
	int total=0;
	for(;i<n-1;i++)
	{  
		if(*(L->elem+i-1)>*(L->elem+i)&&*(L->elem+(i+1)%n)>*(L->elem+i)) total++;
		if(*(L->elem+i-1)<*(L->elem+i)&&*(L->elem+(i+1)%n)<*(L->elem+i)) total++; 
	}
	return total;
}
int main()
{
	int n;
	int total;
	Sqlist L;
	printf("请输入你想放入的值\n");
	scanf("%d",&n);
	InitList(&L);
	createList(&L,n);
	total=TurnPoint(&L,n);
	printf("\n%d\n",total);
	return 0;
} 
