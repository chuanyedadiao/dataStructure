#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

int N,M,K;

typedef struct Side
{
	int num;
	struct Side *next;
}Side;

typedef struct Node
{
	int keynum;
	Side *next;
}Node;

typedef struct 
{
	Node *base;
	int length;
}NodeList;

typedef struct 
{
	int *foundnum;
	int length;
}FindList;

void CreateNode(NodeList *nodelist)
{
	nodelist->base=(Node*)malloc(N*sizeof(Node));
	int i=0;
	while(i<N)
	{
		nodelist->base[i].keynum=i+1;
		nodelist->base[i].next=(Side*)malloc(sizeof(Side));
		nodelist->base[i].next=NULL;
		i++;
	}
	nodelist->length=N;
}

void CreateSides(NodeList *nodelist)
{
	int j=0;
	int begin,end,sidelength;
	Side *p,*q;
	while(j<M)
	{
		scanf("%d%d",&begin,&end);
		p=(Side*)malloc(sizeof(Side));
		p->num=end;
	    p->next=nodelist->base[begin-1].next;
	    nodelist->base[begin-1].next=p;
	    q=(Side*)malloc(sizeof(Side));
		q->num=begin;
	    q->next=nodelist->base[end-1].next;
	    nodelist->base[end-1].next=q;
	    j++;
	}
}

void CreateFindList(FindList *findlist)
{
	int s=0;
	findlist->foundnum=(int*)malloc(K*sizeof(int));
	while(s<K)
	{
		scanf("%d",(findlist->foundnum+s));
		s++;
	}
	findlist->length=K; 
}

int FindLength(NodeList nodelist,int i,int target)
{
	int length=0;
	int min_length=N-1;
	Side *p;
	p=nodelist.base[target].next;
	while(p)
	{
		if(p->num==i+1)
		{
			min_length=1;
		    break;	
		}
		p=p->next;
	}//如果在该结点中能够找到则返回1 
	if(!p)
	{
		p=nodelist.base[target].next;
		while(p)
		{
			length=FindLength(nodelist,i,p->num-1);
			if(min_length>length+1) min_length=length+1;
			p=p->next;
		}
	}//如果找不到就对target的每个连接的点进行寻找，最后返回length 
	return min_length;
}

void OutResult(NodeList *nodelist,int value)
{
	int target=value-1;
	int TotalLength=0;
	int i=0;
	while(i<nodelist->length)
	{
		if(i==target)
		{
			i++;
			continue;
		}
		TotalLength+=FindLength(*nodelist,i,target);
		i++;
	}
	printf("Cc(%d)=%.2f\n",value,(float)(N-1)/TotalLength);
}

int main()
{
	NodeList nodelist;
	FindList findlist;
	scanf("%d%d",&N,&M);
	CreateNode(&nodelist);
	CreateSides(&nodelist);
	scanf("%d",&K);
	CreateFindList(&findlist);
	int find=0;
	while(find<K)
	{
		OutResult(&nodelist,findlist.foundnum[find]);
		find++;
	}
	return 0;
}
/*
5 8
1 2
1 3
1 4
2 3
3 4
4 5
2 5
3 5
2 4 3 
*/
 
