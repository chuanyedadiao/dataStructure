#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct list
{
	int data;
	struct list *next;
}LNode,*LinkList;
LinkList InitList()
{
	LinkList L;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	return L;
}
void createList(LinkList list,int n)
{
	LNode *p,*q;
	p=list;
	int i;
	for(i=0;i<n;i++)
	{
	    q=(LNode *)malloc(sizeof(LNode));
		p->next=q;
		printf("输入数据\n");
		scanf("%d",&q->data);
		p=q;
	}
	p->next=NULL;
}
void reserve(LinkList list)
{
	LNode *p,*q,*s;
	q=list->next;
	if(q==NULL) printf("该表为空表");
	else{
		list->next=NULL;
		p=NULL;
		s=q->next;
		while(s)
		{
			s=q->next;
			list->next=q;
			q->next=p;
			p=q;
			q=s;
		}
	}
}
void output(LinkList list)
{
	LNode *p,*q;
	p=list;
	q=p->next;
	while(q)
	{
		printf("%d\t",q->data);
		p=q;
		q=p->next;
	}
}

int main()
{
	LinkList L;
	int n;
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺\n");
	L=InitList();
	printf("请输入你想输入的数据的个数\n");
	scanf("%d",&n);
	if(n==0) printf("该链表为空表！\n");
	else{
		createList(L,n);
	    printf("逆序之前\n");
	    output(L);
	    reserve(L);
	    printf("\n逆序之后\n");
	    output(L);
    }
	return 0;
}
