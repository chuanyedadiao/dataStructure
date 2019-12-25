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
		printf("��������\n");
		scanf("%d",&q->data);
		p=q;
	}
	p->next=NULL;
}
void reserve(LinkList list)
{
	LNode *p,*q,*s;
	q=list->next;
	if(q==NULL) printf("�ñ�Ϊ�ձ�");
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
	printf("ѧ��:031720106\n����:����˳\n");
	L=InitList();
	printf("������������������ݵĸ���\n");
	scanf("%d",&n);
	if(n==0) printf("������Ϊ�ձ�\n");
	else{
		createList(L,n);
	    printf("����֮ǰ\n");
	    output(L);
	    reserve(L);
	    printf("\n����֮��\n");
	    output(L);
    }
	return 0;
}
