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
		printf("输入数据\n");
		scanf("%d",&q->data);
		Insert_Sort(list,q);
	}
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
	LinkList A,B,C;
	int num_A,num_B;
	A=InitList();
	B=InitList();
	printf("Please enter the number of A you want to initialize\n");
	scanf("%d",&num_A);
	createList(A,num_A);
	printf("Please enter the number of B you want to initialize\n");
	scanf("%d",&num_B);
	createList(B,num_B);
	C=A;
	MergeList(C,B);
	printf("插入排序后遍历\n");
	ListTraverse(C);
	return 0;
} 
