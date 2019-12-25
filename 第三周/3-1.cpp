 #include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct sqstack{
	int *base;
	int *top;
	int stacksize;
}SqStack;

void InitStack(SqStack *stack)
{
	stack->base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
	if(!stack->base) 
	{
		printf("创建栈失败！"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}
void DestroyStack(SqStack *stack)
{
	free(stack->base);
	stack->stacksize=0;
	stack->base=NULL;
	stack->top=NULL;
	printf("销毁栈成功！");
}
void ClearStack(SqStack *stack)
{
	stack->top=stack->base;
	printf("清空栈成功！");
}
void StackEmpty(SqStack stack)
{
	if(stack.top-stack.base!=0)
	{
		printf("该栈不为空!"); 
	}
	else printf("该栈为空");
}
int StackLength(SqStack stack)
{
	return (stack.top-stack.base);
}
int GetTop(SqStack *stack,int *e)
{
	if(stack->top-stack->base==0){
		printf("该栈为空!");
		return 0;
	}
	*e=*(stack->top-1);
	return 1;
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
void visit(int e)
{
	printf("%d\t",e);
}
void StackTraverse(SqStack stack)
{
	int *p=stack.base;
	if(stack.top-stack.base==0) 
	{
		printf("该栈为空！");
		return ;
	}
	while(p<stack.top)
	{
		visit(*p);
		p++;
	}
}
void CreateStack(SqStack *stack,int n)
{
	int i;
	stack->top=stack->base;
	if(n>stack->stacksize)
	{
		stack->base=(int *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(int));
		stack->top=stack->base; 
		stack->stacksize+=STACKINCREMENT;
	}
	if(!stack->base){
		printf("在向栈中给元素时，重新分配空间出错！");
		return;
	}
	for(i=0;i<n;i++)
	{
		printf("请输入数:"); 
		scanf("%d",stack->base+i);
		stack->top++;
	}
}

int main()
{
	SqStack stack;
	int m=-1,n;
	int judge,length,ele,i;
	while(m!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺");
	printf("请输入需要进行的操作：\n");
	printf("1.InitStack\n");
	printf("2.DeleteStack\n");
	printf("3.ClearStack\n");
	printf("4.StackEmpty\n");
	printf("5.StackLength\n");
	printf("6.GetTop\n");
	printf("7.Push\n");
	printf("8.Pop\n");
	printf("9.StackTraverse\n");
	printf("10.CreateStack\n");
	printf("0.exit\n");
	scanf("%d",&m);
	switch(m)
	{
		case 1:{
			system("cls");
			InitStack(&stack);
			printf("已成功创建栈\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyStack(&stack); 
			printf("已成功销毁了栈\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			ClearStack(&stack);
			printf("成功清空了栈\n");
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			StackEmpty(stack);
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			length=StackLength(stack);
			printf("当前栈的长度为%d.",length);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			judge=GetTop(&stack,&ele);
			system("pause");
			if(judge==0){
				break;
			}
			printf("栈顶元素为%d\n",ele);
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			printf("请输入你想插入到栈顶的数据：\n");
			scanf("%d",&ele);
			Push(&stack,ele);
			system("pause");
			break;
		}
		case 8:{ 
			system("cls");
			Pop(&stack,&ele);
			printf("从栈顶弹出的元素是:%d\n",ele);
			system("pause");
			break;
		}
		case 9:{ 
			system("cls");
			printf("遍历后：\n");
			StackTraverse(stack);
			system("pause");
			break;
		}
		case 10:{ 
			system("cls");
		    printf("请输入你想放入的数据数\n");
			scanf("%d",&n);
			CreateStack(&stack,n);	
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
