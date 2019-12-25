#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct lnode
{
	int data;
	struct lnode *next;
}LNode,*LinkList;
LinkList InitList()
{
	LinkList L;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	return L;
}
void Insert_Sort(LinkList list,LNode* q)
{
	LNode *p,*s;
	p=list;
	s=p->next;
	if(s==NULL){
		p->next=q;
		q->next=s;
		return;
	}
	while(s&&s->data<q->data)
	{
	    p=s;
		s=p->next;
	}//找到合适的位置 
	q->next=s;
	p->next=q;//插入 
}
void createList(LinkList list,int n)
{
	LNode *p,*q;
	p=list;
	int i;
	for(i=0;i<n;i++)
	{
	    q=(LNode *)malloc(sizeof(LNode));
		printf("输入数据\n");
		scanf("%d",&q->data);
		Insert_Sort(list,q);
	}
}
int visit(int m)
{
	printf("%d\t",m);
} 
void ListTraverse(LinkList list)
{
	LNode *p,*q;
	p=list;
	q=p->next;
	while(q)
	{
        visit(q->data);
		p=q;
		q=p->next;
	}
}
int main()
{
	LinkList L;
	int n;
	L=InitList();
	printf("请你输入你想输入的值\n");
	scanf("%d",&n);
	createList(L,n);
	printf("插入排序后遍历\n");
	ListTraverse(L);
	return 0;
} 
