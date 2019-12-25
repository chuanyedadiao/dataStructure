#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct queue
{
	struct queue *front;
	int data;
	struct queue* next;
}Queue,*QueueList;
QueueList InitList()
{
	QueueList L;
	L=(QueueList)malloc(sizeof(struct queue));
	L->next=NULL;
	L->front=L;
	return L;
}
void InputsList(QueueList L,int n)
{
	int i=0;
	Queue *p1,*p2,*q1,*q2;
	p1=L;
	q1=L;
	for(;i<n;i++)
	{
		p2=(Queue*)malloc(sizeof(Queue));
		p1->next=p2;
		p1=p2;
		p1->front=q1;
		q1=p1;
		p1->data=i+1;
	}
	p1->next=L;
	L->front=p1;
}
void put(QueueList L,int n)
{
	Queue *p1,*p2;
	int i=0;
	p1=L;
	p2=p1->next;
	while(i<n)
	{
		printf("%d\t",p2->data);
		p1=p2;
		p2=p1->next;
		i++; 
	}
}
void found(QueueList L,int m)
{
	int i;
	int j;
	int num,change;
	bool nex=1,fron=1;
	Queue *p1,*p2,*s1,*s2,*m1;
	p1=L;
	p2=p1->next;
	s1=s2=L;
	for(i=1;i<=m;i++)
	{
		printf("����������Ҫ�ı��ѧ���Լ���θı�\n");
		scanf("%d%d",&num,&change);
		if(change>0)
		{
			while(p2)
			{
				if(p2->data==num)
				{
					m1=p2;
					for(j=0;j<change;j++){
						if(m1->next==L) break;
						m1=m1->next;
					}
					p1->next=p2->next;
					p2->next->front=p1;
					p2->next=m1->next;
					m1->next->front=p2;
					m1->next=p2;
					p2->front=m1;
				    break;
				}
			p1=p2;
			p2=p1->next;
			}	
		}
		if(change<0)
		{
			while(p2)
			{
				if(p2->data==num)
				{
					m1=p2;
					for(j=0;j>change;j--){
						if(m1->front==L) break;
						m1=m1->front;
					}
					p1->next=p2->next;
					p2->next->front=p1;
					m1->front->next=p2;
					p2->front=m1->front;
					p2->next=m1;
					m1->front=p2;
				    break;
				}
			p1=p2;
			p2=p1->next;
		    }   
	    }
    } 
}
int main()
{
	QueueList L;
	int n,m;
	system("date/t");
	system("time/t");
	printf("ѧ��:031720106\n����:����˳\n");
	L=InitList();
	printf("�����������\n");
	scanf("%d",&n);
	printf("��������ı�Ĵ���:\n");
	scanf("%d",&m);
	if(n==0) printf("������Ϊ��");
	else{
		InputsList(L,n);
	    printf("�任֮ǰ��\n");
	    put(L,n);
	    printf("\n");
	    found(L,m);
	    printf("�任֮��\n");
	    put(L,n);
	}
	return 0;
}
