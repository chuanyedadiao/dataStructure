#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

int N,M;

typedef struct Node
{
	int value;
	bool used;
}Node;

typedef struct List
{
	Node *elem;
	int length;
}Goods,Coupons;

void CreateGoods(Goods *goods)
{
	goods->elem=(Node*)malloc(N*sizeof(Node));
	if(!goods->elem)
	{
		printf("Create Goods fail!\n");
		exit(0);
	}
	int i=0;
	while(i<N)
	{
		scanf("%d",&goods->elem[i].value);
		goods->elem[i].used=0;
		i++;
	}
	goods->length=N;
}

void CreateCoupons(Coupons *coupons)
{
	coupons->elem=(Node*)malloc(M*sizeof(Node));
	if(!coupons->elem)
	{
		printf("Create Coupons fail!\n");
		exit(0);
	}
	int i=0;
	while(i<M)
	{
		scanf("%d",&coupons->elem[i].value);
		coupons->elem[i].used=0;
		i++;
	}
	coupons->length=M;
}

int Partition(struct List *list,int low,int high)
{
	int t,i,j,key;
	i=low;
	j=high;
	key=list->elem[low].value;
	while(i<j)
	{
		while(i<j&&list->elem[j].value>=key) j--;
		list->elem[i].value=list->elem[j].value;
		while(i<j&&list->elem[i].value<=key) i++;
		list->elem[j].value=list->elem[i].value;
	}
	list->elem[i].value=key;
	return i;
} 

void QSort(struct List *list,int low,int high)
{
	int key;
	if(low<high)
	{
		key=Partition(list,low,high);
		QSort(list,low,key-1);
		QSort(list,key+1,high);
    }
}

int Calculate(Goods goods,Coupons coupons)
{
	int i=goods.length-1,j=coupons.length-1;
	int max=0;
	int total,result=0;
	int goodsflag=-1,couponsflag=-1;
	while(i>=0)
	{
		while(j>=0)
		{
			if(goods.elem[i].used!=1&&coupons.elem[j].used!=1&&(goods.elem[i].value)*(coupons.elem[i].value)>0)
			{
				total=(goods.elem[i].value)*(coupons.elem[j].value);
				if(max<total)
				{
					max=total;
					goodsflag=i;
					couponsflag=j;
				}
			}
			j--;
		}
		if(goodsflag!=-1)
		{
			goods.elem[goodsflag].used=1;
			coupons.elem[couponsflag].used=1;
			result+=max;
		}
		i--;
		j=coupons.length-1;
		goodsflag=-1;
		couponsflag=-1;
		max=0;
	}
	return result;
} 

int main()
{
	Goods goods;
	Coupons coupons;
	int Max_result;
	scanf("%d",&N);
	CreateGoods(&goods);
	scanf("%d",&M);
	CreateCoupons(&coupons);
	QSort(&goods,0,N-1);
	QSort(&coupons,0,M-1);//进行快速排序
	Max_result=Calculate(goods,coupons);
	printf("%d\n",Max_result);
	return 0; 
}

/*
4 1 2 4 -1
4 7 6 -2 -3

4 3 2 6 1 
3 2 6 3

7 3 36 -1 73 2 3 6
6 -1 -1 -1 -1 -1 -1
*/
