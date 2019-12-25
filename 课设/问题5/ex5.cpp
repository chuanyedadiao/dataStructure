#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
int n,m;

typedef struct Point
{
	int RoadKind;
	int point;
	int RoadLength;
	struct Point *next;
}Point;

typedef struct Node
{
	int node;
	Point *relate;
}Node;

typedef struct PList
{
	Node *base;
	int length;
}PList;

typedef struct 
{
	int point;
	int exhaust;
}RoadNode;

typedef struct Road
{
	RoadNode *base;
	int length;
}Road;

typedef struct Stack
{
	int *base;
	int *top;
	int stacksize;
}Stack;

void InitList(PList *list)
{
	list->base=(Node *)malloc(n*sizeof(Node)); 
	if(!list->base)
	{
		printf("�������˳���ʧ�ܣ�\n");
		exit(0);
	}
	list->length=n;
	int i=0;
	while(i<list->length)
	{
		(list->base+i)->node=i+1;
		(list->base+i)->relate=(Point*)malloc(sizeof(Point));
		(list->base+i)->relate->next=NULL;
		i++;
	}
}

void InputRelatePoint(PList *list,FILE *input)
{
	int type,begin,end,roadlength;
	fscanf(input,"%d%d%d%d",&type,&begin,&end,&roadlength);
	Point *p;
	Node *q;
	q=list->base;
	int i=0;
	while(!feof(input))
	{
		while(i<list->length)
		{
			if(q->node==begin)
			{
				p=(Point *)malloc(sizeof(Point));
				p->RoadKind=type;
				p->RoadLength=roadlength;
				p->point=end;
				p->next=q->relate->next;
				q->relate->next=p;//��ͷ�巨 
			}
			if(q->node==end)
			{
				p=(Point*)malloc(sizeof(Point));
				p->RoadKind=type;
				p->RoadLength=roadlength;
				p->point=begin;
				p->next=q->relate->next;
				q->relate->next=p;
			}
			i++;
			q++;
		}
		i=0;
		q=list->base;
		fscanf(input,"%d%d%d%d",&type,&begin,&end,&roadlength);
	}
}

void InitRoad(Road *road)
{
	road->base=(RoadNode*)malloc(n*(sizeof(RoadNode)));
	if(!road->base)
	{
		printf("����ʧ��\n");
		exit(0);
	}
	road->length=0;
}

void InitStack(Stack *stack)
{
	stack->base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!stack->base) 
	{
		printf("����ջʧ�ܣ�"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}

void ClearStack(Stack *stack)
{
	stack->top=stack->base;
}

int TraverseStack(Stack stack)
{
	int *p;
	int total=0;
	p=stack.base;
	while(p!=stack.top)
	{
		total+=(*p);
		p++;
	}
	return total;
}

void Push(Stack **stack,int e)
{
	if((*stack)->top-(*stack)->base==STACK_INIT_SIZE)
	{
		(*stack)->base=(int *)realloc((*stack)->base,((*stack)->stacksize+STACKINCREMENT)*sizeof(int));
		(*stack)->top=(*stack)->base+(*stack)->stacksize;
		(*stack)->stacksize+=STACKINCREMENT;
	}
	if(!(*stack)->base){
		printf("����Ԫ��ʱջ�������·���ռ����");
		return;
	}
    *((*stack)->top)=e;
    (*stack)->top++;
}

int ExsitInRoad(Road *road,int point)
{
	RoadNode *p;
	p=road->base;
	int i=0;
	while(i<road->length)
	{
		if(p->point==point)
		{
			return 1;
		}
		i++;
		p++;
	}
	return 0;
}

int Froad(PList list,int begin,int *key,int exhaust,Stack *stack,Road **road)
{
	Node *p;
	Point *q;
	p=list.base;
	q=p->relate->next;
	*key=0;
	int i=0,flag,min=0x100;
	int insertlength;
	int tag;
	int lastexhaust;
	while(i<list.length)
	{
		if(p->node==begin)
		{
			while(q)
			{
				if(ExsitInRoad(*road,q->point))
				{
					q=q->next;
					continue;
				}
				if(q->RoadKind==0)
				{
					flag=exhaust+q->RoadLength;
				}
				if(q->RoadKind==1)
				{
					lastexhaust=TraverseStack(*stack);//�۲��������˶���С��
					flag=exhaust-(lastexhaust)*(lastexhaust)+(lastexhaust+q->RoadLength)*(lastexhaust+q->RoadLength);
				}
				if(flag<min)
				{
					min=flag;
					tag=q->RoadKind;
					if(tag==1)
					{
						insertlength=q->RoadLength;
					}
					(*key)=q->point;
				}
				q=q->next;
			}
			((*road)->base+(*road)->length)->point=*key;
			((*road)->base+(*road)->length)->exhaust=min;
			(*road)->length++;
			if(tag==0)
			{
				ClearStack(stack);
			}
			else Push(&stack,insertlength); 
			break;
		}
		i++;
		p++;
		q=p->relate->next;
	}
	return min;
}

void FindRoad(PList list,int start,int end,int *totalexhaust,Stack stack,Road *road)
{
	int exhaust;
	int key;
	if(start!=end)
	{
		exhaust=Froad(list,start,&key,*totalexhaust,&stack,&road);
		if(key==0)
		{
			printf("����Ѱ�������㲻��ͨ\n");
			exit(0);
		}
		*totalexhaust=exhaust;
		FindRoad(list,key,end,totalexhaust,stack,road);
	}
}

void OutputRoad(Road road)
{
	int i=0;
	RoadNode *p=road.base;
	printf("��Сƣ�Ͷȵ�·����\n");
	while(i<road.length)
	{
		printf("%d ",p->point);
		p++;
		i++;
	}
	printf("\n");
}

void Result(PList list,int end)
{
	Stack stack;
	Road road;
	int totalexhaust;
	InitRoad(&road);
	road.base->point=1;
	road.base->exhaust=0;
	road.length++;
	InitStack(&stack);
	FindRoad(list,1,end,&totalexhaust,stack,&road);
	if(end==n)
	{
		printf("%d\n",totalexhaust);
		OutputRoad(road);
	} 
	else printf("%d->%d %d\n",1,end,totalexhaust);
	free(stack.base);
	free(road.base);
	totalexhaust=0;//Ϊʲôtotalexhaust���Ǿ�̬�������Ǽ̳���֮ǰ��ֵ?? 
}

int main()
{
	FILE *input;
	PList list;
	input=fopen("Road.txt","r");
	fscanf(input,"%d%d",&n,&m);
	InitList(&list);
	InputRelatePoint(&list,input);
	Result(list,n);
	int i=2;
	while(i<list.length)
	{
		Result(list,i);
		i++;
	}
	return 0;
}
