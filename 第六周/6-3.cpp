#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct Bitnode
{
	char data;
	struct Bitnode *Child,*Sibling;
}BiTNode,*BiTree;

BiTree InitBiTree()
{
	BiTree T;
	T=(BiTree)malloc(sizeof(BiTNode));
	T->Child=NULL;
	T->Sibling=NULL;
	return T;
}

void CreateBiTree(BiTree *T) 
{
	char ch;
	ch=getchar();
	if(ch=='#') *T=NULL;
	else{
		*T=(BiTNode*)malloc(sizeof(BiTNode));
		if(!*T) exit(0);
		(*T)->data=ch;
		CreateBiTree(&(*T)->Child);
		CreateBiTree(&(*T)->Sibling);
	}
	return;
}

int TreeHeight(BiTree T)
{
	BiTNode *p;
	int m,max=0;
	p=T;
	if(T==NULL) return 0;
	else if(T->Child==NULL) return 1;
	else {
		p=p->Child;
		while(p)
		{
			m=TreeHeight(p);
			if(max<m) max=m;
			p=p->Sibling;
		}//找到兄弟中最大的子树
		return max+1; 
	}
}
int main()
{
	BiTree T;
	T=InitBiTree();
	CreateBiTree(&T);
	BiTNode *q;
	q=T;
	int totalmax=0,flag;
	while(q)
	{
		flag=TreeHeight(q);
		if(flag>totalmax) totalmax=flag;
		q=q->Sibling;
	}
	printf("TreeHeight=%d\n",totalmax);
	return 0;
} 
