#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define INFINITY 0x100
#define MAX_VERTEX_NUM 26
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
int ve[MAX_VERTEX_NUM]={0};
int vl[MAX_VERTEX_NUM]={INFINITY};

typedef struct ArcCell
{
	int adj;
	int *info;//弧的信息 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	char vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;

typedef struct sqstack{
	char *base;
	char *top;
	int stacksize;
}SqStack;
typedef struct  QNode
{
	char data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct Link
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
void CreateDN(MGraph *G)
{
	int w,i,j;
	int IncInfo;
	printf("输入点的个数边数和info相关信息\n");
	scanf("%d%d%d",&G->vexnum,&G->arcnum,&IncInfo);
	printf("输入点\n");
	for(i=0;i<G->vexnum;i++) {
		getchar();
		scanf("%c",&G->vexs[i]);
	}
	for(i=0;i<G->vexnum;i++)
	    for(j=0;j<G->vexnum;j++)
	        G->arcs[i][j]={INFINITY,NULL};
	for(int k=0;k<G->arcnum;k++)
	{
		scanf("%d%d%d",&i,&j,&w); 
		G->arcs[i-1][j-1].adj=w;
		if(IncInfo); 
	} 
}

void InitStack(SqStack *stack)
{
	stack->base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!stack->base) 
	{
		printf("创建栈失败！"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}

void Push(SqStack *stack,char e)
{
	if(stack->top-stack->base==STACK_INIT_SIZE)
	{
		stack->base=(char *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(char));
		stack->top=stack->base+stack->stacksize;
		stack->stacksize+=STACKINCREMENT;
	}
	if(!stack->base){
		printf("插入元素时栈满，重新分配空间出错！");
		return;
	}
    *(stack->top)=e;
    stack->top++;
}

void InitQueue(LinkQueue *Q)
{
	Q->front=(QueuePtr)malloc(sizeof(QNode));
	Q->rear=Q->front;
	Q->front->next=NULL;
}
void EnQueue(LinkQueue *Q,char e)
{
	QNode *p;
	p=(QNode*)malloc(sizeof(QNode));
	Q->rear->next=p;
	p->data=e;
	Q->rear=p;
	p->next=NULL;
}
void DeQueue(LinkQueue *Q,char *e)
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
	free(p);
}
int QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear){
		return 1;
	}
	else return 0;
}

int Judge(char flag[],char e)
{
	int i=0;
	while(flag[i]!='\0')
	{
		if(flag[i]==e) return 1;
		i++;
	}
	return 0;
}

void Path(MGraph G,SqStack *stack)
{
	int indegree[MAX_VERTEX_NUM]={0};
	int i,j,cnt=0,CNT=0;
	char flag[MAX_VERTEX_NUM]={0};
	LinkQueue S;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		    if(G.arcs[j][i].adj!=INFINITY)
			{
		    	cnt++;
		    }
	    indegree[i]=cnt;
		cnt=0; 
	}//对各个顶点求入度
	InitQueue(&S);
	for(i=0;i<G.vexnum;i++)
        if(indegree[i]==0){
        	EnQueue(&S,G.vexs[i]);
        	flag[CNT]=G.vexs[i];
        	CNT++;
        }
    InitStack(stack);
    int count=0;
    char e;
    while(!QueueEmpty(S))
    {
    	DeQueue(&S,&e);
    	Push(stack,e);
    	count++;
    	for(i=0;i<G.vexnum;i++)
            if(e==G.vexs[i]) break;
        for(j=0;j<G.vexnum;j++)
        {
            if(G.arcs[i][j].adj!=INFINITY&&indegree[j]>0) indegree[j]--;//对应的顶点的每个邻接点入度减一
            if(Judge(flag,G.vexs[j])==0&&indegree[j]==0){
            	EnQueue(&S,G.vexs[j]);
            	flag[CNT]=G.vexs[j];
            	CNT++;
            } 
        }
    }
}
void print(SqStack stack)
{
	char *p;
	p=stack.base;
	while(p!=stack.top)
	{
		printf("%c  ",*p);
		p++;
	}
}
int main()
{
	MGraph G;
	CreateDN(&G);
	SqStack stack;
    Path(G,&stack);
    print(stack);
	return 0;
}
