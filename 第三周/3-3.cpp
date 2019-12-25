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
int startlist=0;//��ʼ���� 

void InitStack(SqStack *stack)
{
	stack->base=(Site*)malloc(STACK_INIT_SIZE*sizeof(Site));
	if(!stack->base) 
	{
		printf("����ջʧ�ܣ�"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}
void Pop(SqStack *stack)
{
	if(stack->top-stack->base==0)
	{
		printf("��ջΪ�գ�");
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
		printf("����Ԫ��ʱջ�������·���ռ����");
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
}//�����ж����λ�ú�ջ�е�Ԫ�ص�����Ĺ�ϵ 
void visit(Site e)
{ 
	printf("(%d,%d)",e.x+1,e.y+1);
}//��� 
void StackTraverse(SqStack stack)
{
	Site *p=stack.base;
	if(stack.top-stack.base==0) 
	{
		printf("��ջΪ�գ�");
		return ;
	}
	printf("%d:  ",count);
	while(p<stack.top)
	{
		visit(*p);
		p++;
	}
}//����ջ�����Ԫ�� 
int EmptyStack(SqStack *stack)
{
	if(stack->top-stack->base==0)
        return 0;
	else 
	return 1;
}//�ж��Ƿ�Ϊ�� 
void EightQueen(SqStack *stack)
{
	Site ele[10][10];
	Site *e;
	int i,j,k=0;
	int sign=1;
	bool decide=0;
	for(i=0;i<8;i++)//��ʼ���������� 
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
			StackTraverse(*stack);//��� 
			k=(stack->top-1)->y+1;//�����һ�� 
			Pop(stack);//������ջtop���۲��Ƿ���������λ���ʺ� 
			i--;
			printf("\n");
		}//���а˸������һ��
		j=k;
		for(;j<8;j++){
			if(Judge(stack,ele[i][j]))//�ж��Ƿ�������� 
		    {
		    	CNT++;
				decide=1;
				Push(stack,ele[i][j]);//���ϣ�push 
				i++;
				k=0;//��jҪ��0��ʼ����k��0 
				break;
		    }//�жϸõ��Ƿ��ʺ���������������������ջ��k=0����ʾ����һ�п�ʼ 
	    }
		if(decide==0){//�ж��Ƿ�����ʺϵĵ� 
			sign=EmptyStack(stack);
			if(!sign) break;
			k=(stack->top-1)->y+1;//k=��һ����������һ��������һ�� 
			Pop(stack);
			i--;
			CNT--;
		}//�жϸ����Ƿ���ջ�����û����ջ���򵯳���һ�㣬������һ���yֵ��ʼѡ�� 
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
