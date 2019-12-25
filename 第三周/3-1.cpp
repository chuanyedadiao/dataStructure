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
		printf("����ջʧ�ܣ�"); 
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
	printf("����ջ�ɹ���");
}
void ClearStack(SqStack *stack)
{
	stack->top=stack->base;
	printf("���ջ�ɹ���");
}
void StackEmpty(SqStack stack)
{
	if(stack.top-stack.base!=0)
	{
		printf("��ջ��Ϊ��!"); 
	}
	else printf("��ջΪ��");
}
int StackLength(SqStack stack)
{
	return (stack.top-stack.base);
}
int GetTop(SqStack *stack,int *e)
{
	if(stack->top-stack->base==0){
		printf("��ջΪ��!");
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
		printf("����Ԫ��ʱջ�������·���ռ����");
		return;
	}
    *(stack->top)=e;
    stack->top++;
}
void Pop(SqStack *stack,int *e)
{
	if(stack->top-stack->base==0)
	{
		printf("��ջΪ�գ�");
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
		printf("��ջΪ�գ�");
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
		printf("����ջ�и�Ԫ��ʱ�����·���ռ����");
		return;
	}
	for(i=0;i<n;i++)
	{
		printf("��������:"); 
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
	printf("ѧ��:031720106\n����:����˳");
	printf("��������Ҫ���еĲ�����\n");
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
			printf("�ѳɹ�����ջ\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyStack(&stack); 
			printf("�ѳɹ�������ջ\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			ClearStack(&stack);
			printf("�ɹ������ջ\n");
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
			printf("��ǰջ�ĳ���Ϊ%d.",length);
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
			printf("ջ��Ԫ��Ϊ%d\n",ele);
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			printf("������������뵽ջ�������ݣ�\n");
			scanf("%d",&ele);
			Push(&stack,ele);
			system("pause");
			break;
		}
		case 8:{ 
			system("cls");
			Pop(&stack,&ele);
			printf("��ջ��������Ԫ����:%d\n",ele);
			system("pause");
			break;
		}
		case 9:{ 
			system("cls");
			printf("������\n");
			StackTraverse(stack);
			system("pause");
			break;
		}
		case 10:{ 
			system("cls");
		    printf("��������������������\n");
			scanf("%d",&n);
			CreateStack(&stack,n);	
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
