#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


typedef struct
{
	double *base;
	double *top;
	int stacksize;
}Operand_Stack;

typedef struct 
{
	char *base;
	char *top;
	int stacksize
}Operator_Stack;

void InitOperandStack(Operand_Stack *stack)
{
	stack->base=(double*)malloc(STACK_INIT_SIZE*sizeof(double));
	if(!stack->base)
	{
		printf("Create Operand_Stack fail\n");
		exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}

void InitOperatorStack(Operator_Stack *stack)
{
	stack->base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!stack->base)
	{
		printf("Create Operator_Stack fail\n");
		exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}

int main()
{
	
}



 
