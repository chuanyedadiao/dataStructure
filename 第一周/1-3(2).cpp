#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct list
{
	int data;
	struct list* next;
}LNode,*LinkList;
LinkList InitList()
{
	LinkList L;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=L;
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
		printf("��������:");
		scanf("%d",&q->data);
		p=q;
	}
	p->next=list;
}
void out(LinkList L,int n,int m)
{
	LNode *p,*q;
	p=L;
	q=p->next;
	if(q==NULL) return;
	int i=1,j;
	while(i<=n)
	{
		for(j=1;j<m;j++)
		{
			p=q;
			q=p->next;
			if(q==L){
				q=q->next;
			}
		}
		printf("%d:\t%d\n",i,q->data);
		if(q->next==L) {
		p->next=q->next->next;
		q=p->next;
		}
		else{
		p->next=q->next;
		q=p->next;
		}
		i++;
	}
}
int main()
{
	LinkList L;
	int n,m;
	L=InitList();
	system("date/t");
	system("time/t");
	printf("ѧ��:031720106\n����:����˳\n");
	printf("���������ݵĸ���\n");
	scanf("%d",&n);
	printf("������ѭ�������������ٳ��У�\n");
	scanf("%d",&m);
	if(n==0) printf("������Ϊ�ձ�\n");
	else{
		createList(L,n);
		out(L,n,m);
	}
	return 0;
} 
