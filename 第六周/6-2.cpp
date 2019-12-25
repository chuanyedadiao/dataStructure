#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

void Select(HuffmanTree HT,int *s1,int *s2,int i)
{
	int j,min1,min2;
	HTNode *p;
	p=HT;
	min1=0x100;
	min2=0x100;
	for(j=0;j<i;p++,j++)
	{
		if(p->parent==-1&&min1>=p->weight)
		{
			min1=p->weight;
			*s1=j;
		}
	}
	p=HT;
	for(j=0;j<i;p++,j++)
	{
		if(p->parent==-1&&min2>p->weight&&j!=*s1)
		{
			min2=p->weight;
			*s2=j;
		}
	}
} 
void HuffmanCreate(HuffmanTree *HT,int w[],int n)
{
	int m,s1,s2,i,j,t;
	HTNode *p;
	if(n<=1) return;
	m=2*n-1;
	*HT=(HuffmanTree)malloc(m*sizeof(HTNode));
	for(p=*HT,i=0;i<n;p++,i++)
	{
		p->weight=w[i];
		p->lchild=-1;
		p->rchild=-1;
		p->parent=-1;
	}
	for(;i<m;i++,p++)
	{
		p->weight=0;
		p->lchild=-1;
		p->rchild=-1;
		p->parent=-1;
	}
	p=*HT;
	for(i=n;i<m;i++)
	{
		Select(*HT,&s1,&s2,i);
		if(s1>s2){
			t=s1;
			s1=s2;
			s2=t;
		}
		(p+s1)->parent=i;
		(p+s2)->parent=i;
		(p+i)->lchild=s1;
		(p+i)->rchild=s2;
		(p+i)->weight=(p+s1)->weight+(p+s2)->weight;
	} 
} 

int main()
{
	HuffmanTree HT;
	int i,n,w[100];
	printf("«Î ‰»În(1-100)\n");
	scanf("%d",&n);
	printf(" ‰»Î÷µ\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&w[i]);
	}
	HuffmanCreate(&HT,w,n);
	HTNode *p;
	p=HT;
	for(i=0;i<2*n-1;i++,p++)
	{
		printf("%d:%d\t%d\t%d\t%d\n",i+1,p->weight+1,p->parent+1,p->lchild+1,p->rchild+1);
	}
	return 0;
}
//8
//5 29 7 8 14 23 3 11
