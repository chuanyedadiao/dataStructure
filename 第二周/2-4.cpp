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
	LNode *p,*s,*t;
	p=list;
	s=p->next;
	t=(LNode*)malloc(sizeof(LNode));
	t->data=q->data;
	if(s==NULL){
		p->next=t;
		t->next=s;
		return;
	}
	while(s&&s->data<q->data)
	{
	    p=s;
		s=p->next;
	}
	if(s&&s->data==q->data){
		p->next=s->next;
		free(s);
		s=p->next;
	}
	t->next=s;
	p->next=t;
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
		printf("ÊäÈëÊý¾Ý\n");
		scanf("%d",&q->data);
		p=q;
	}
	p->next=NULL;
}
void MergeList(LinkList C,LinkList B)
{
	LNode *pb,*qb,*mb;
	pb=B;
	qb=pb->next;
	if(qb==NULL) return;
	mb=qb->next;
	while(mb)
	{
		Insert_Sort(C,qb);
		qb=mb;
		mb=mb->next;
	}
	Insert_Sort(C,qb);
}
void Judge(LinkList C)
{
	LNode *p,*p1,*q,*q1;
	p1=q1=C->next;
	int SmallCNT=0,BigCNT=0;
	bool m=0;
	while(p1)
	{
		while(q1)
		{
			if(q1->data>p1->data) BigCNT++;
			if(q1->data<p1->data) SmallCNT++;
			q1=q1->next;
		}
		if(SmallCNT==BigCNT&&SmallCNT!=0&&BigCNT!=0) 
		{
		    printf("\n%d\n",p1->data);
		    m=1;
		}
		SmallCNT=0;
		BigCNT=0;
		q1=C->next;
		p1=p1->next;
	}
	if(!m) printf("\n-1\n");
}
int main()
{
	LinkList B,C;
	int num_B;
	C=InitList();
	B=InitList();
	printf("Please enter the number of B you want to initialize\n");
	scanf("%d",&num_B);
	createList(B,num_B);
	MergeList(C,B);
	Judge(C);
	return 0;
} 
