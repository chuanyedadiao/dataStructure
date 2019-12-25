//递归

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void InitBiTree(BiTree *T)
{
	*T=(BiTree)malloc(sizeof(BiTNode));
	(*T)->lchild=NULL;
	(*T)->rchild=NULL;
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
	if(T==NULL) return;
	else{
		Visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	if(T==NULL) return;
	else{
		InOrderTraverse(T->lchild);
		Visit(T->data);
		InOrderTraverse(T->rchild);
	}
} 

void PostOrderTraverse(BiTree T)
{
	if(T==NULL) return;
	else{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		Visit(T->data);
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
