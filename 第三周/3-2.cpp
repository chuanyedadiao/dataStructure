#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct  QNode
{
	int data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct Link
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
void InitQueue(LinkQueue *Q)
{
	Q->front=(QueuePtr)malloc(sizeof(QNode));
	Q->rear=Q->front;
	Q->front->next=NULL;
	printf("�������гɹ�!\n");
}
void DestroyQueue(LinkQueue *Q)
{
	QNode *p,*q;
	p=Q->front;
	q=p->next;
	while(q)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
	printf("���ٶ��гɹ�!\n");
}
void ClearQueue(LinkQueue *Q)
{
	Q->rear=Q->front;
	printf("����б�ɹ���");
}
void QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear){
		printf("�ö���Ϊ�գ�");
	}
	else printf("�ö��в�Ϊ�գ�");
}
int QueueLength(LinkQueue Q)
{
	int length=0;
	QNode *p;
	p=Q.front->next; 
	while(p!=NULL)
	{
		length++;
		p=p->next;
	}
	return length;
}
void GetHead(LinkQueue *Q,int *e)
{
	if(Q->front==Q->rear)
	{
		printf("�ö���Ϊ��");
		return; 
	}
	QNode *p;
	p=Q->front->next;
	*e=p->data;
	printf("����ͷ��Ԫ��Ϊ:%d",*e);
} 
void EnQueue(LinkQueue *Q,int e)
{
	QNode *p;
	p=(QNode*)malloc(sizeof(QNode));
	Q->rear->next=p;
	p->data=e;
	Q->rear=p;
	p->next=NULL;
	printf("�Ѳ�����Ԫ��%d\n",e);
}
void DeQueue(LinkQueue *Q,int *e)
{
	if(Q->front==Q->rear)
	{
		printf("�ö���Ϊ��");
		return ;
	}
	QNode *p,*q;
	p=Q->front->next;
	*e=p->data;
	q=p->next;
	Q->front->next=q;
	if(Q->rear==p) Q->rear=Q->front;
	free(p);
	printf("��ɾ����ͷ��Ԫ�أ�%d\n",*e);
}
void visit(int e)
{
	printf("%d\t",e);
}
void QueueTraverse(LinkQueue Q)
{
	if(Q.front==Q.rear){
		printf("�ö���Ϊ�գ�");
		return ;
	}
	QNode *p;
	p=Q.front->next;
    printf("����������������Ԫ��\n");
	while(p!=NULL)
	{
		visit(p->data);
		p=p->next;
	}
}
void CreateQueue(LinkQueue *Q,int n)
{
	int i;
	QNode *p,*q;
	p=Q->front;
	for(i=0;i<n;i++)
	{
		q=(QNode*)malloc(sizeof(QNode));
		printf("��������������ֵ:");
		scanf("%d",&q->data);
		p->next=q;
		Q->rear=q;
		p=q;
	}
	Q->rear->next=NULL;
}
int main()
{
	LinkQueue Q;
	int m=-1,n;
	int length;
	bool judge;
	int ele;
	int i;
	int pre_e,next_e;
	while(m!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("ѧ��:031720106\n����:����˳");
	printf("��������Ҫ���еĲ�����\n");
	printf("��������Ҫ���еĲ�����\n");
	printf("1.InitQueue\n");
	printf("2.DestroyQueue\n");
	printf("3.ClearQueue\n");
	printf("4.QueueEmpty\n");
	printf("5.QueueLength\n");
	printf("6.GetHead\n");
	printf("7.EnQueue\n");
	printf("8.DeQueue\n");
	printf("9.QueueTraverse\n");
	printf("10.CreateQueue\n");
	printf("0.exit\n");
	scanf("%d",&m);
	switch(m)
	{
		case 1:{
			system("cls");
			InitQueue(&Q);
			printf("�ѳɹ���������\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyQueue(&Q);
			printf("�ѳɹ������˶���\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			ClearQueue(&Q);
			printf("�ɹ�����˶���\n");
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			QueueEmpty(Q);
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			length=QueueLength(Q);
			printf("��ǰ����ĳ���Ϊ%d.",length);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			GetHead(&Q,&ele);
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			printf("�����������ڶ����в�������ݣ�\n");
			scanf("%d",&ele);
			EnQueue(&Q,ele);
			system("pause");
			break;
		}
		case 8:{ 
			system("cls");
			DeQueue(&Q,&ele);
			system("pause");
			break;
		}
		case 9:{ 
			system("cls");
			QueueTraverse(Q);
			system("pause");
			break;
		}
		case 10:{ 
			system("cls");
		    printf("�����������������ݵĸ�����\n");
			scanf("%d",&n);
			CreateQueue(&Q,n);
			system("pause");
			break;
		}
		case 0:{
			printf("�ѳɹ��˳���\n");
			exit(0);
			break;
		}
	}
	}
	return 0;
}
