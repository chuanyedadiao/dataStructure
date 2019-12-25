#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct site{
	int x;
	int y;
}Site;
typedef struct sqstack{
	Site *base;
	Site *top;
	int stacksize;
}SqStack;
int CNT=0;
int count=0;
int startlist=0;//初始的列 

void InitStack(SqStack *stack)
{
	stack->base=(Site*)malloc(STACK_INIT_SIZE*sizeof(Site));
	if(!stack->base) 
	{
		printf("创建栈失败！"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}
void Pop(SqStack *stack)
{
	if(stack->top-stack->base==0)
	{
		printf("该栈为空！");
		return ;
	}
	stack->top--;
}
void Push(SqStack *stack,Site e)
{
	if(stack->top-stack->base==STACK_INIT_SIZE)
	{
		stack->base=(Site *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(Site));
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
int Judge(SqStack *stack,Site e)
{
	Site* p;
	bool judge=1;
	p=stack->base;
	while(p<stack->top)
	{
		if((e.y==p->y)||(e.x==p->x)||(e.y-e.x==p->y-p->x)||(e.y+e.x==p->y+p->x)){
			judge=0;
		}
		p++;
	}
	return judge;
}//用于判断这个位置和栈中的元素的坐标的关系 
void visit(Site e)
{ 
	printf("(%d,%d)",e.x+1,e.y+1);
}//输出 
void StackTraverse(SqStack stack)
{
	Site *p=stack.base;
	if(stack.top-stack.base==0) 
	{
		printf("该栈为空！");
		return ;
	}
	printf("%d:  ",count);
	while(p<stack.top)
	{
		visit(*p);
		p++;
	}
}//遍历栈里面的元素 
int EmptyStack(SqStack *stack)
{
	if(stack->top-stack->base==0)
        return 0;
	else 
	return 1;
}//判断是否为空 
void EightQueen(SqStack *stack)
{
	Site ele[10][10];
	Site *e;
	int i,j,k=0;
	int sign=1;
	bool decide=0;
	for(i=0;i<8;i++)//初始化整个矩阵 
	{
		for(j=0;j<8;j++)
		{
			ele[i][j].x=i;
			ele[i][j].y=j;
		}
	}
    for(i=0;;){
    	if(CNT==8)
	    {
			count++;
			CNT--;
			StackTraverse(*stack);//输出 
			k=(stack->top-1)->y+1;//向后走一步 
			Pop(stack);//弹出来栈top，观察是否有其他的位置适合 
			i--;
			printf("\n");
		}//若有八个则输出一次
		j=k;
		for(;j<8;j++){
			if(Judge(stack,ele[i][j]))//判断是否符合条件 
		    {
		    	CNT++;
				decide=1;
				Push(stack,ele[i][j]);//符合，push 
				i++;
				k=0;//则j要从0开始，将k置0 
				break;
		    }//判断该点是否适合条件，若符合条件，入栈，k=0即表示从下一行开始 
	    }
		if(decide==0){//判断是否存在适合的点 
			sign=EmptyStack(stack);
			if(!sign) break;
			k=(stack->top-1)->y+1;//k=上一层的纵坐标加一，往后走一步 
			Pop(stack);
			i--;
			CNT--;
		}//判断该行是否入栈，如果没有入栈，则弹出上一层，并从上一层的y值开始选择 
		decide=0;
    } 
}

int main()
{
	SqStack stack;
	InitStack(&stack);
	EightQueen(&stack);
	return 0;
}
