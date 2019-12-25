#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MAXSIZE 12500
typedef struct triple{
	int x;
	int y;
	int data;
}Triple;

typedef struct{
	Triple* elem;
	int mu;//行数 
	int nu;//列数
	int tu;//非零元素 
}TSMatrix;

void InitTSMatrix(TSMatrix *T)
{
	T->elem=(Triple*)malloc(MAXSIZE*sizeof(Triple));
	if(!T->elem){
		printf("Error\n");
		exit(0);
	}
	T->mu=0;
	T->nu=0;
	T->tu=0;
}

void CreateTSMatrix(TSMatrix *T)
{
	printf("Please Input the mu and nu and tu of TSMatrix:\n");
	scanf("%d%d%d",&T->mu,&T->nu,&T->tu);
	int i;
	for(i=0;i<T->tu;i++)
	{
		printf("输入矩阵非零元素的坐标和值的大小：");
		scanf("%d%d%d",&(T->elem+i)->x,&(T->elem+i)->y,&(T->elem+i)->data);
	}
} 

void PrintMatrix(TSMatrix T)
{
	int i,j,k=0;
	for(i=0;i<T.mu;i++)
	{
		for(j=0;j<T.nu;j++)
		{
			if(i==(T.elem+k)->x-1&&j==(T.elem+k)->y-1){
				printf("%d\t",(T.elem+k)->data);
				k++;
			}
			else printf("0\t");
		}
		printf("\n");
	}
}

void SortMatrix(TSMatrix *T)
{
	int i;
	int j;
	Triple m;
	for(i=0;i<T->tu;i++)
	{
		for(j=0;j<T->tu-i-1;j++)
		{
			if((T->elem+j+1)->x<(T->elem+j)->x){
				m=*(T->elem+j);
				*(T->elem+j)=*(T->elem+j+1);
				*(T->elem+j+1)=m;
			}//冒泡 
			if((T->elem+j+1)->x==(T->elem+j)->x){
			    if((T->elem+j+1)->y<(T->elem+j)->y){
				    m=*(T->elem+j);
				    *(T->elem+j)=*(T->elem+j+1);
				    *(T->elem+j+1)=m;    
			    }
				else continue;   	
			}//如果相等就要比较纵坐标 
		}
	}
} //排序 

void TransposeSMatrix(TSMatrix T,TSMatrix *M)
{
	int col,p;
	int k;
	if(T.tu)//若T中有元素 
	{
		p=0;
		for(col=0;col<T.nu;col++)
		{
			for(k=0;k<T.tu;k++)
			{
				if((T.elem+k)->y==col+1){//其中某个元素的列等于行的值 
					(M->elem+p)->x=(T.elem+k)->y;
					(M->elem+p)->y=(T.elem+k)->x;
					(M->elem+p)->data=(T.elem+k)->data;
					p++;
				}
			}
		}
	}
	M->mu=T.nu;
	M->nu=T.mu;
	M->tu=T.tu;
}

int main()
{
	TSMatrix T,M;
	InitTSMatrix(&T);
	InitTSMatrix(&M);
	CreateTSMatrix(&T);
	SortMatrix(&T);
	printf("原矩阵：\n");
	PrintMatrix(T);
	TransposeSMatrix(T,&M);
	printf("\n转置矩阵：\n");
	PrintMatrix(M);
	return 0;
}
