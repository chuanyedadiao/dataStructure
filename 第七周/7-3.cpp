#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define INFINITY 0x100
#define MAX_VERTEX_NUM 100
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct ArcCell
{
	int adj;
	int *info;//弧的信息 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	int vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;

typedef struct sqstack{
	int *base;
	int *top;
	int stacksize;
}SqStack;

void CreateUDN(MGraph *G)
{
	int i,j,w;
	int n,m;
	printf("输入n和m\n");
	scanf("%d%d",&n,&m);
	G->vexnum=n;
	G->arcnum=m;
	for(i=0;i<G->vexnum;i++){
		G->vexs[i]=i+1;
	}
	for(i=0;i<G->vexnum;i++)
	    for(j=0;j<G->vexnum;j++)
	        G->arcs[i][j]={INFINITY,NULL};
	for(int k=0;k<G->arcnum;k++)
	{
		scanf("%d%d%d",&i,&j,&w);
		G->arcs[i-1][j-1].adj=w;
		G->arcs[j-1][i-1]=G->arcs[i-1][j-1]; 
	} 
}

void InitStack(SqStack *stack)
{
	stack->base=(int*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!stack->base) 
	{
		printf("创建栈失败！"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}
void Push(SqStack *stack,int e)
{
	if(stack->top-stack->base==STACK_INIT_SIZE)
	{
		stack->base=(int *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(int));
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
void Pop(SqStack *stack,int *e)
{
	if(stack->top-stack->base==0)
	{
		printf("该栈为空！");
		return ;
	}
	*e=*(stack->top-1);
	stack->top--;
}
int StackEmpty(SqStack stack)
{
	if(stack.top-stack.base!=0)
	{
		return 0; 
	}
	else return 1;
}
int Judge(MGraph G,int *e,int flag[])
{
	int i,j,k;
	int tag=-1,final_tag=-1;
	int min=INFINITY;
	int Graph_min=min;
	int cnt=0;
	while(flag[cnt]!=0)
	{
		i=flag[cnt]-1;
		for(j=0;j<G.vexnum;j++)
		{
			for(k=0;k<G.vexnum;k++)
			{
				if(G.vexs[j]==flag[k]){
					break;
				}
			}
			if(k==G.vexnum&&G.arcs[i][j].adj<min){
				min=G.arcs[i][j].adj;
				tag=G.vexs[j];
			}
			k=0;
		}
		if(min<Graph_min)
		{
			Graph_min=min;
			*e=i+1;
			final_tag=tag;
		}
		cnt++;
	}
	return final_tag;
}

int Result(MGraph G,int out[])
{
	int e1,e2;
	out[0]=G.vexs[0];
	e2=G.vexs[0];
	int CNT=1,min_total=0;
	while(CNT<G.vexnum)
	{
		e1=Judge(G,&e2,out);
		out[CNT]=e1;
		min_total+=G.arcs[e2-1][e1-1].adj;
		CNT++;
		e2=e1;
	}
	return min_total;
}

int main()
{
	MGraph G;
	CreateUDN(&G);
	int min_total;
	int output[MAX_VERTEX_NUM]={0};
	min_total=Result(G,output);
	printf("\n%d",min_total);
	return 0;
}


/*
6 10
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 5 6
3 6 4
4 6 2
5 6 6
*/

