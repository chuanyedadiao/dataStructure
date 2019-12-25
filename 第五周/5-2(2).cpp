//非递归

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct sqstack{
	BiTNode* *base;
	BiTNode* *top;
	int stacksize;
}SqStack;

void InitStack(SqStack *stack)
{
	stack->base=(BiTNode**)malloc(STACK_INIT_SIZE*sizeof(BiTNode*));
	if(!stack->base) 
	{
		printf("创建栈失败！"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}

int StackEmpty(SqStack stack)
{
	if(stack.top-stack.base!=0)
	{
		return 0; 
	}
	else return 1;
}

void InitBiTree(BiTree *T)
{
	*T=(BiTree)malloc(sizeof(BiTNode));
	(*T)->lchild=NULL;
	(*T)->rchild=NULL;
}

void Push(SqStack *stack,BiTNode* e)
{
	if(stack->top-stack->base==STACK_INIT_SIZE)
	{
		stack->base=(BiTNode* *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(BiTNode*));
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

void GetTop(SqStack *stack,BiTNode* *e)
{
	if(stack->top-stack->base==0){
		printf("该栈为空!");
	}
	*e=*(stack->top-1);
}

void Pop(SqStack *stack,BiTNode* *e)
{
	if(stack->top-stack->base==0)
	{
		printf("该栈为空！");
		return ;
	}
	*(e)=*(stack->top-1);
	stack->top--;
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
}//先序

void Visit(char e)
{
	printf("%c",e);
}

void PreOrderTraverse(BiTree T)
{
	BiTNode *p=T;
	SqStack stack;
	InitStack(&stack);
	Push(&stack,T);
	while(StackEmpty(stack)!=1)
	{
		GetTop(&stack,&p);
		if(p!=NULL){
			Visit(p->data);
			Pop(&stack,&p);
			Push(&stack,p->rchild);
			Push(&stack,p->lchild);
		}
		else Pop(&stack,&p);
	}
}

void InOrderTraverse(BiTree T)
{	
    BiTNode *p=T;
	SqStack stack;
	InitStack(&stack);
	Push(&stack,T);
	while(StackEmpty(stack)!=1)
	{
		GetTop(&stack,&p);
		while(p){
			Push(&stack,p->lchild);
			GetTop(&stack,&p);
		} 
		Pop(&stack,&p);
		if(StackEmpty(stack)!=1){
			Pop(&stack,&p);
			Visit(p->data);
			Push(&stack,p->rchild);
		}
	}
}

void PostOrderTraverse(BiTree T)
{
	BiTNode *p=T,*q=T;
	int flag=1;
	SqStack stack;
	InitStack(&stack);
	Push(&stack,T);
	while(StackEmpty(stack)!=1)
	{
		GetTop(&stack,&p);
		while(p&&flag)
		{
			GetTop(&stack,&p);
			while(p){
				Push(&stack,p->lchild);
				GetTop(&stack,&p);
			}//往左走，走到尽头 
			Pop(&stack,&p);//弹出空 
			GetTop(&stack,&p);
			p=p->rchild;
			Push(&stack,p);
		}
		if(flag) Pop(&stack,&p);//弹出空 
		if(StackEmpty(stack)!=1) 
		{
			Pop(&stack,&p);
			Visit(p->data);
			q=p;
			if(StackEmpty(stack)!=1)
			{
			    GetTop(&stack,&p);
				if(q==p->lchild)
				{
				    flag=1;
					Push(&stack,p->rchild);
				}
				else flag=0;	
			}
		}
	}
}

int main()
{
	BiTree T;
	InitBiTree(&T);
	CreateBiTree(&T);
	printf("\n先序:\n");
	PreOrderTraverse(T);
	printf("\n中序:\n");
	InOrderTraverse(T);
	printf("\n后序:\n");
	PostOrderTraverse(T);
	return 0;
}
