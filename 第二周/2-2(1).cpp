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
	p=list->elem;
	int i,j;
	for(i=0;i<list->length;i++)
	{
		if(m<*(list->elem+i)) break;
	}
	for(j=list->length;j>i;j--)
	{
		*(list->elem+j)=*(list->elem+j-1);
	}
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
		Insert_Sort(list,*(list->elem+i));
	}
}
void MergeList(Sqlist *LC,Sqlist *LA,Sqlist *LB)
{
	int i=0;
	int *newbase;
	while(i<LB->length)
	{
	    if(LC->length>=LC->listsize)
	    {
		    newbase=(int*)realloc(LC->elem,(LC->listsize+LISTINCERMENT)*sizeof(int));
		    LC->elem=newbase;
		    LC->listsize+=LISTINCERMENT;
	    }
		Insert_Sort(LC,*(LB->elem+i));
		i++;
		LC->length++;
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
	Sqlist A,B,C;
	InitList(&A);
	InitList(&B);
	int num_A,num_B;
	printf("Please enter the number of A you want to initialize\n");
	scanf("%d",&num_A);
	createList(&A,num_A);
	printf("Please enter the number of B you want to initialize\n");
	scanf("%d",&num_B);
	createList(&B,num_B);
	C=A;
	MergeList(&C,&A,&B);
	printf("合并A和B后的C的遍历\n");
	ListTraverse(C);
	return 0; 
}

