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
}

void DeleteSon(BiTree *T)
{
	BiTNode *p;
	p=*(T);
	if(p==NULL)
	{
		free(p);
	}
	else{
		DeleteSon(&p->lchild);
		DeleteSon(&p->rchild);
		free(p);
	}
} 
int DeleteTNode(BiTree *T,char e)
{
	int judge=0;
	if(*T==NULL) return 0;
	if((*T)->data==e)
	{
	     DeleteSon(T);
		 return 1;	
	}
	else{
		if(DeleteTNode(&(*T)->lchild,e))
		{
			(*T)->lchild=NULL;
		}
	    if(DeleteTNode(&(*T)->rchild,e))
		{
			(*T)->rchild=NULL;
		}
	}
	return 0;
}

void Visit(char e)
{
	printf("%c",e);
}
void PreOrderTraverse(BiTree T)
{
	if(T==NULL){
		return;
	}
	else{
		Visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

int main()
{
	BiTree T;
	InitBiTree(&T);
	CreateBiTree(&T);
	PreOrderTraverse(T);
	char e;
	getchar();
	printf("\n请输入你想删除的节点\n");
	scanf("%c",&e);
	if(T->data==e) 
	{
		DeleteTNode(&T,e);
		T=NULL;
	}
	else DeleteTNode(&T,e);
	PreOrderTraverse(T);
	return 0;
}
