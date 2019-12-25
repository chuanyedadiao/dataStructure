#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define INFINITY 0x100
#define MAX_VERTEX_NUM 26
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef enum{DG,DN,UDG,UDN}GraphKind;
typedef struct ArcCell
{
	int adj;
	int *info;//弧的信息 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	char vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
	GraphKind kind;
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

void CreateDG(MGraph *G)
{
	int IncInfo,i,j;
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
		scanf("%d%d",&i,&j);
		G->arcs[i-1][j-1].adj=1;
		if(IncInfo); 
	} 
}
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
void CreateUDG(MGraph *G)
{
	int i,j,IncInfo;
	printf("输入点的个数边数和info相关信息\n");
	scanf("%d%d%d",&G->vexnum,&G->arcnum,&IncInfo);
	printf("输入点\n");
	for(i=0;i<G->vexnum;i++)
	{
		getchar();
		scanf("%c",&G->vexs[i]);
	}
	for(i=0;i<G->vexnum;i++)
	    for(j=0;j<G->vexnum;j++)
	        G->arcs[i][j]={INFINITY,NULL};
	printf("输入对应的边或权值\n");
	for(int k=0;k<G->arcnum;k++)
	{
		scanf("%d%d",&i,&j);
		G->arcs[i-1][j-1].adj=1;
		if(IncInfo);
		G->arcs[j-1][i-1]=G->arcs[i-1][j-1]; 
	} 
}
void CreateUDN(MGraph *G)
{
	int i,j,w;
	int IncInfo;
	printf("输入点的个数边数和info相关信息\n");
	scanf("%d%d%d",&G->vexnum,&G->arcnum,&IncInfo);
	printf("输入点\n");
	for(i=0;i<G->vexnum;i++){
		getchar();
		scanf("%c",&G->vexs[i]);
	}
	for(i=0;i<G->vexnum;i++)
	    for(j=0;j<G->vexnum;j++)
	        G->arcs[i][j]={INFINITY,NULL};
	printf("输入对应的边或权值\n");
	for(int k=0;k<G->arcnum;k++)
	{
		scanf("%d%d%d",&i,&j,&w);
		G->arcs[i-1][j-1].adj=w;
		if(IncInfo);
		G->arcs[j-1][i-1]=G->arcs[i-1][j-1]; 
	} 
}
void CreateGraph(MGraph *G)
{
	int i; 
	GraphKind a[4];
	a[0]=DG;
	a[1]=DN;
	a[2]=UDG;
	a[3]=UDN;
	printf("DG,DN,UDG,UDN\n");
	scanf("%d",&i);
	G->kind=a[i-1];
	switch(G->kind)
	{
		case DG:{
			CreateDG(G);
			break;
		}
		case DN:{
			CreateDN(G);
			break;
		}
		case UDG:{
			CreateUDG(G);
			break;
		}
		case UDN:{
			CreateUDN(G);
			break;
		}
	}
}
void DestroyGraph(MGraph *G)
{
	return;
}
int LocateVex(MGraph G,char u)
{
	int i=0;
	while(G.vexs[i]!=u)
	{
		i++;
	}
	return i;
}
char GetVex(MGraph G,char v)
{
	int i=0;
	while(G.vexs[i]!=v)
	{
		i++;
	}
	if(i>=G.vexnum) return '#';
	else return G.vexs[i];
}
void PutVex(MGraph *G,char v,char value)
{
	int i=0;
	while(G->vexs[i]!=v){
		i++;
	}
	if(i>=G->vexnum) {
		printf("该顶点不在图G中\n");
		return ;
	}
	else {
		G->vexs[i]=value;
		printf("修改成功\n");
	}
}
char FirstAdjVex(MGraph G,char v)
{
	int i;
	while(G.vexs[i]!=v){
		i++;
	}
	if(i>=G.vexnum) return 0;
	else{
		int j=0;
		while(G.arcs[i][j].adj==INFINITY)
		{
			j++;
		}
		if(j>=G.vexnum) return 0;
		else return G.vexs[j];
	}
}
char NextAdjVex(MGraph G,char v,char w)
{
	int i=0,k;
	while(G.vexs[i]!=v){
		i++;
	}
	k=i;
	if(i>=G.vexnum) return 0;
	else{
		i=0;
		while(G.vexs[i]!=w){
		    i++;
	    }
	    if(G.arcs[k][i].adj==INFINITY||i==G.vexnum-1) return 0;
	    else{
		    int j=i+1;
			while(G.arcs[k][j].adj==INFINITY)
			{
				j++;
			}
			if(j>=G.vexnum) return 0;
			else return G.vexs[j];
	    }	
	}
}

void InsertVex(MGraph *G,char v)
{ 
	if(G->vexnum>=MAX_VERTEX_NUM)
	{
		printf("超出最大值\n");
		return ;
	}
	int m,n;
	printf("请输入插入该顶点的位置\n");
	scanf("%d",&n);
	m=n-1;
	int i,j;
	for(i=G->vexnum-1;i>=m;i--)
	{
		G->vexs[i+1]=G->vexs[i];
	}
	G->vexs[m]=v;
	G->vexnum++;
	for(i=0;i<G->vexnum-1;i++)
	{
		for(j=G->vexnum;j>m;j--)
		   G->arcs[i][j]=G->arcs[i][j-1];
		G->arcs[i][m]={INFINITY,NULL};
	}
	for(j=0;j<G->vexnum;j++)
	{
		for(i=G->vexnum;i>m;i--)
		   G->arcs[i][j]=G->arcs[i-1][j];
		G->arcs[m][j]={INFINITY,NULL};
    }
	int arc_num;
	int p,IncInfo,w;
	printf("请输入你想加入的边的条数以及边的信息\n"); 
	scanf("%d%d",&arc_num,&IncInfo);
	printf("分别输入与该顶点有边的顶点以及（权值）\n");
	for(i=0;i<arc_num;i++)
	{
		if(G->kind==DN||G->kind==UDN)
		{
			scanf("%d%d",&p,&w);
			G->arcs[m][p-1].adj=w;
			if(IncInfo);
			G->arcs[p-1][m]=G->arcs[m][p-1]; 
		}
		else{
		    scanf("%d",&p);
			G->arcs[m][p-1].adj=1;
			if(IncInfo);
			G->arcs[p-1][m]=G->arcs[m][p-1]; 
		}
	}
}
void DeleteVex(MGraph *G,char v)
{
	int m,i,j;
	m=LocateVex(*G,v);
	if(m>=G->vexnum){
		printf("该顶点不在图中\n");
		return ;
	} 
	for(i=m;i<G->vexnum;i++)
	{
		G->vexs[i]=G->vexs[i+1];
	}
	for(i=0;i<G->vexnum;i++)
	{
		for(j=m;j<G->vexnum;j++)
		    G->arcs[i][j]=G->arcs[i][j+1];
	}
	for(j=0;j<G->vexnum;j++)
	{
		for(i=m;i<G->vexnum;i++)
		    G->arcs[i][j]=G->arcs[i+1][j];
	}
	G->vexnum--;
}
void InsertArc(MGraph *G,char v,char w)
{
	int i,j;
	int weight;
	i=LocateVex(*G,v);
	j=LocateVex(*G,w);
	if(G->arcs[i][j].adj!=INFINITY){
		printf("该边已存在\n");
		return ;
	}
	switch (G->kind)
	{
		case DG:{
			G->arcs[i][j].adj=1;
			break;
		}
		case DN:{
			printf("输入v,w的权值\n");
			scanf("%d",&weight);
			G->arcs[i][j].adj=weight;
			break;
		}
		case UDG:{
			G->arcs[i][j].adj=1;
			G->arcs[j][i].adj=1;
			break;
		}
		case UDN:{
			printf("输入v,w的权值\n");
			scanf("%d",&weight);
			G->arcs[i][j].adj=weight;
			G->arcs[j][i].adj=weight;
			break;
		}
	}
}
void DeleteArc(MGraph *G,char v,char w)
{
	int i,j;
	i=LocateVex(*G,v);
	j=LocateVex(*G,w);
	if(G->arcs[i][j].adj==INFINITY)
	{
		printf("该边不存在\n");
		return; 
	}
	switch(G->kind)
	{
		case DG:{
			G->arcs[i][j].adj=INFINITY;
			break;
		}
		case DN:{
			G->arcs[i][j].adj=INFINITY;
			break;
		}
		case UDG:{
			G->arcs[i][j].adj=INFINITY;
			G->arcs[j][i].adj=INFINITY;
			break;
		}
		case UDN:{
			G->arcs[i][j].adj=INFINITY;
			G->arcs[j][i].adj=INFINITY;
			break;
		}
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
void Pop(SqStack *stack,char *e)
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
void GetTop(SqStack *stack,char *e)
{
	if(stack->top-stack->base==0){
		printf("该栈为空!");
		return; 
	}
	*e=*(stack->top-1);
}

void InitQueue(LinkQueue *Q)
{
	Q->front=(QueuePtr)malloc(sizeof(QNode));
	Q->rear=Q->front;
	Q->front->next=NULL;
}
void GetHead(LinkQueue *Q,char *e)
{
	if(Q->front==Q->rear)
	{
		printf("该队列为空");
		return; 
	}
	QNode *p;
	p=Q->front->next;
	*e=p->data;
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
int JudgeStack(SqStack stack,char e)
{
	char *p;
	p=stack.base;
	while(p<stack.top)
	{
		if(*p==e) return 1;
		p++;
	}
	return 0;
}
int JudgeQueue(LinkQueue Q,char e)
{
	QNode *p;
	p=Q.front->next;
	while(p)
	{
		if(p->data==e) return 1;
		p=p->next;
	}
	return 0;
}
char FirstStackVex(MGraph G,char e,SqStack stack,char sign[])
{
	int i,j=0,k=0;
	bool judge=0;
	i=LocateVex(G,e);
	while(j<G.vexnum)
	{
	    while(sign[k]!='\0')
		{
			if(G.vexs[j]==sign[k])
		    {
		    	judge=1;
		    	break;
		    }
		    k++;
		}
		if(judge!=1&&G.arcs[i][j].adj!=INFINITY&&!JudgeStack(stack,G.vexs[j])) return G.vexs[j];
		j++;
		k=0;
		judge=0;
	}
	return 0;
}
char FirstQueueVex(MGraph G,char e,LinkQueue Q,char sign[])
{
	int i,j=0,k=0;
	bool judge=0;
	i=LocateVex(G,e);
	while(j<G.vexnum)
	{
		while(sign[k]!='\0')
		{
			if(G.vexs[j]==sign[k])
		        judge=1;
			k++;
		}
		if(judge!=1&&G.arcs[i][j].adj!=INFINITY&&!JudgeQueue(Q,G.vexs[j])) return G.vexs[j];
		j++;
		judge=0;
		k=0;
	}
	return 0;
}
void visit(char e)
{
	printf("%c\t",e);
}
void DFSTraverse(MGraph G)
{
	SqStack stack;
	InitStack(&stack);
	char start,m;
	char e;
	char sign[MAX_VERTEX_NUM]={0};
	int CNT=0;
	start=G.vexs[0];
	Push(&stack,start);
	GetTop(&stack,&e);
	visit(e);
	sign[CNT]=e;
	CNT++;
	while(!StackEmpty(stack)&&CNT!=G.vexnum)
	{
		while((m=FirstStackVex(G,e,stack,sign))!=0)
		{
			Push(&stack,m);
			GetTop(&stack,&e);
			sign[CNT]=e;
	        visit(e);
	        CNT++;
		}
		if(CNT!=G.vexnum)
		{
		    while((m=FirstStackVex(G,e,stack,sign))==0)
		    {
		    	Pop(&stack,&e);
		    }
		}
		
	}
}
void BFSTraverse(MGraph G)
{
	LinkQueue Q;
	InitQueue(&Q);
	char start,m;
	char e;
	char sign[MAX_VERTEX_NUM]={0};
	int cnt=0;
	start=G.vexs[0];
	EnQueue(&Q,start);
	while(!QueueEmpty(Q))
	{
		while((m=FirstQueueVex(G,e,Q,sign))!=0)
		{
			EnQueue(&Q,m);
		}
		DeQueue(&Q,&e);
		sign[cnt]=e;
		cnt++;
		visit(e);
		GetHead(&Q,&e); 
	}
}

int main()
{
	int key=1;
	MGraph G;
	while(key!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺");
	printf("请输入需要进行的操作：\n");
	printf("请输入需要进行的操作：\n");
	printf("1.CreateGraph\n");
	printf("2.DestroyGraph\n");
	printf("3.LocateVex\n");
	printf("4.GetVex\n");
	printf("5.PutVex\n");
	printf("6.FirstAdjVex\n");
	printf("7.NextAdjVex\n");
	printf("8.InsertVex\n");
	printf("9.DeleteVex\n");
	printf("10.InsertArc\n");
	printf("11.DeleteArc\n");
	printf("12.DFSTraverse\n");
	printf("13.HFSTraverse\n"); 
	printf("0.exit\n");
	scanf("%d",&key);
	switch(key)
	{
		case 1:{
			system("cls");
			CreateGraph(&G);
			printf("已成功创建图\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyGraph(&G);
			printf("已成功销毁了图\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			int locate;
			char u,e;
			getchar();
			printf("请输入想找到的顶点\n");
			scanf("%c",&u);
			locate=LocateVex(G,u);
			if(locate==G.vexnum) printf("该顶点不在图中\n");
			else printf("该顶点为图中第%d个顶点\n",locate+1);
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			char v;
			char e;
			getchar();
			printf("请输入你想找到的顶点\n");
			scanf("%c",&v);
			e=GetVex(G,v);
			if(e=='#') printf("该顶点不存在\n");
			else printf("该顶点存在，且值为%c\n",e);
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			char v,value;
			getchar();
			printf("请输入你想改变的顶点以及改变为何值\n");
			scanf("%c %c",&v,&value);
		    PutVex(&G,v,value);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			char v;
			char e;
			getchar();
			printf("请输入想找到的哪个顶点的第一个邻接顶点\n");
			scanf("%c",&v);
			e=FirstAdjVex(G,v);
			if(e==0) printf("该顶点不在图中\n");
			else printf("该顶点第一个邻接顶点是%c\n",e);
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			char v,w,e;
			getchar();
			printf("请输入v,w\n");
			scanf("%c %c",&v,&w);
			e=NextAdjVex(G,v,w);
			if(e==0) printf("该顶点不在图中，或w不在图中\n");
			else printf("v的邻接顶点在w之后的第一个是%c\n",e);
			system("pause");
			break;
		}
		case 8:{ 
			system("cls");
			char v;
			getchar();
			printf("请输入你想插入的顶点\n");
			scanf("%c",&v);
			InsertVex(&G,v);
			system("pause");
			break;
		}
		case 9:{ 
			system("cls");
			char v;
			getchar();
			printf("请输入你想删除的顶点\n");
			scanf("%c",&v);
			DeleteVex(&G,v);
			system("pause");
			break;
		}
		case 10:{ 
			system("cls");
			char v,w;
			getchar();
			printf("请输入你想插入的弧的起止点\n");
			scanf("%c %c",&v,&w);
			InsertArc(&G,v,w);
			system("pause");
			break;
		}
		case 11:{ 
			system("cls");
			char v,w;
			getchar();
			printf("请输入你想删除的弧的起止点\n");
			scanf("%c %c",&v,&w);
			DeleteArc(&G,v,w);
			system("pause");
			break;
		}
		case 12:{ 
			system("cls");
			printf("深度遍历为\n");
			DFSTraverse(G);
			system("pause");
			break;
		}
		case 13:{
			system("cls");
			printf("广度遍历\n");
			BFSTraverse(G);
			system("pause");
			break;
		}
		case 0:{
			printf("已成功退出！\n");
			exit(0);
			break;
		}
	}
	}
	return 0;
}

/*
3
6 10 0
A B C D E F
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
1 2 
1 3 
1 4 
2 3 
2 5 
3 4 
3 5 
3 6 
4 6
5 6 
*/
