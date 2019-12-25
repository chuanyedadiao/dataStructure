//层次

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct  QNode
{
	BiTNode* data;
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
}

int QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear){
		return 1;
	}
	else return 0;
}

void DeQueue(LinkQueue *Q,BiTNode **e)
{
	if(Q->front==Q->rear)
	{
		printf("该队列为空");
		return ;
	}
	QNode *p,*q;
	p=Q->front->next;
	*e=p->data;
	q=p->next;
	Q->front->next=q;
	if(Q->rear==p) Q->rear=Q->front;
}

void EnQueue(LinkQueue *Q,BiTNode* e)
{
	QNode *p;
	p=(QNode*)malloc(sizeof(QNode));
	Q->rear->next=p;
	p->data=e;
	Q->rear=p;
	p->next=NULL;
}

void InitBiTree(BiTree *T)
{
	*T=(BiTree)malloc(sizeof(BiTNode));
	(*T)->lchild=NULL;
	(*T)->rchild=NULL;
}

void CreateBiTree(BiTree *T)//按先后次序输入二叉树中结点的值，"#"表示空 
{
	char ch;
	ch=getchar();
	if(ch=='#') *T=NULL;
	else{
		*T=(BiTNode*)malloc(sizeof(BiTNode));
		if(!*T) exit(0);
		(*T)->data=ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
	return;
}

void Visit(char e)
{
	printf("%c",e);
}

void LevelOrderTraverse(BiTree T)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p;
	p=T;
	EnQueue(&Q,p);
	while(!QueueEmpty(Q))
	{
		DeQueue(&Q,&p);
		if(p!=NULL){
			EnQueue(&Q,p->lchild);
			EnQueue(&Q,p->rchild);
			Visit(p->data);
		}
	}
}
int main()
{
	BiTree T;
	InitBiTree(&T);
	CreateBiTree(&T);
	printf("层次遍历：\n");
	LevelOrderTraverse(T);
	return 0;
}
