#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;


BiTree InitBiTree()
{
	BiTree T;
	T=(BiTree)malloc(sizeof(BiTNode));
	T=NULL;
	return T;
}

int SearchBST(BiTree T,int e,BiTNode *f,BiTNode **tag)
{
	if(T==NULL){
		*tag=f;
		return 0;
	}
	else if(e==T->data){
		*tag=T;
		return 1;
	}
	else if(e<T->data) return SearchBST(T->lchild,e,T,tag);
	else return SearchBST(T->rchild,e,T,tag);
}

int InsertBST(BiTree *T,int e)
{
	BiTNode *s;
	BiTNode *tag;
	if(!SearchBST(*T,e,NULL,&tag))
	{
		s=(BiTNode*)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=NULL;
		s->rchild=NULL;
		if(tag==NULL) *T=s;
		else if(e<tag->data) tag->lchild=s;
		else tag->rchild=s;
		return 1;
	}
	else return 0;
} //InsertBST

int Delete(BiTree *p)
{
	BiTNode *q,*s;
	if((*p)->rchild==NULL){
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}
	else if((*p)->lchild==NULL)
	{
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}
	else{
		q=*p;
		s=(*p)->lchild;
		while(s->rchild) {
			q=s;
			s=s->rchild;
		}
		(*p)->data=s->data;
		if(q!=*p) q->rchild=s->lchild;
		else q->lchild=s->lchild;
		free(s);
	}
	return 1;
}

int DeleteBST(BiTree *T,int e)
{
	if(T==NULL) return 0;
	else{
		if((*T)->data==e) Delete(T);
		else if(e<(*T)->data) return DeleteBST(&((*T)->lchild),e);
		else return DeleteBST(&((*T)->rchild),e);
	}
}

void Visit(int e)
{
	printf("%d\t",e);
}

void PreOrderTraverse(BiTree T)
{
	if(T==NULL){
		return ;
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
	T=InitBiTree();
	int m;
	int e;
	while(m!=0)
	{
		system("cls");
		printf("insert\n");
		printf("delete\n");
		printf("PreOrderTraverse\n");
		printf("exit\n");
		scanf("%d",&m);
		switch(m)
		{
			case 1:{
				system("cls");
				scanf("%d",&e);
				InsertBST(&T,e);
				system("pause");
				break;
			}
			case 2:{
				system("cls");
				scanf("%d",&e);
				DeleteBST(&T,e);
				system("pause");
				break;
			}
			case 3:{
				system("cls");
				PreOrderTraverse(T);
				system("pause");
				break;
			}
			case 0:{
				exit(0);
				break;
			}
		}
	}
}
