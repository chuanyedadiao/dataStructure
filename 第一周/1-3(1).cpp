#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10
typedef struct list
{
	int length;
	int listsize;
	int *elem;
}List;
void InitList(List *list)
{
	list->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!list->elem) 
	{
		printf("创建顺序表失败！"); 
	    exit(0);
	}
	list->length=0;
	list->listsize=LIST_INIT_SIZE;
	printf("创建顺序表成功！");
}
void createList(List *list,int n)
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
void out(List *L,int m)
{
	int i=L->length,j;
	int mq=1,mp=0;
	int k[100]={0};
	int *p;
	p=L->elem;
	while(i!=0)
	{
		for(j=1;j<=m;j++)  //循环到那个人，以及若指针到末尾，就跳到开头 
		{
		while(k[mp]) mp++;
		p=L->elem+mp;
		mq=mp+1;
		if(mq>L->length){
			mp=0;
			while(k[mp]) mp++;
			p=L->elem+mp;
			mq=mp+1;
		}
    	mp=mq;
		}
		printf("%d:\t%d\n",L->length-i+1,*p);  //输出那个数 
		k[mq-1]=1;
		i--;
	}
}
int main()
{
	List L;
	int n,m;
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺\n");
	InitList(&L);
	printf("请输入该圈的人数:\n");
	scanf("%d",&n);
	printf("请输入循环报数报到多少出列？\n");
	scanf("%d",&m);
	if(n==0) printf("该圈不存在\n");
	else {
		createList(&L,n);
		out(&L,m);
	}
    return 0;
}
