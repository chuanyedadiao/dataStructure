#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct point
{
	int x;
	int y;
}Point;
typedef struct lnode
{
	int num;
	Point low;
	Point high;
	struct lnode *next;
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
		q->num=i+1;
		printf("输入窗口的左下角和右上角的坐标:\n");
		scanf("%d%d%d%d",&q->low.x,&q->low.y,&q->high.x,&q->high.y);
		q->next=p->next;
		p->next=q;
	}
}
void Click(Point points[],int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		scanf("%d%d",&points[i].x,&points[i].y);
	}
}
int Change(LinkList L,Point click)
{
	LNode *p,*q;
	p=L;
	q=p->next;
	if(q==NULL)
	{
		printf("该链表为空！");
		return 0;
	}
	while(q)
	{
		if(click.x>=q->low.x&&click.x<=q->high.x&&click.y>=q->low.y&&click.y<=q->high.y)
		{
			p->next=q->next;
			q->next=L->next;
			L->next=q;
			return q->num; 
		}
		p=q;
		q=p->next;
	}
	if(q==NULL){
		return -1;
	}
}
void Output(LinkList L,Point points[],int m)
{
	int i;
	int number;
	for(i=0;i<m;i++)
	{
		number=Change(L,points[i]);
		if(number==0){
			continue; 
		}
		else if(number==-1){
			printf("IGNORED\n");
		}
		else printf("%d\n",number);
	}
}
int main()
{
	LinkList L;
	int n,m;
	Point points[0x100];
	L=InitList();
	printf("Please enter n and m\n");
	scanf("%d%d",&n,&m);
	createList(L,n);
	Click(points,m);
	Output(L,points,m);
	return 0;
}
