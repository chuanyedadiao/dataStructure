#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10
typedef struct list
{
	int length;
	int listsize;
	int *elem;
}List;
void InitList(List *list)
{
	list->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!list->elem) 
	{
		printf("����˳���ʧ�ܣ�"); 
	    exit(0);
	}
	list->length=0;
	list->listsize=LIST_INIT_SIZE;
	printf("����˳���ɹ���");
}
void createList(List *list,int n)
{
	int i;
	int *newbase;
	for(i=0;i<n;i++)
	{
		if(list->length>=list->listsize)
	{
		newbase=(int*)realloc(list->elem,(list->listsize+LISTINCERMENT)*sizeof(int));
		list->elem=newbase;
		list->listsize+=LISTINCERMENT;
	}
		printf("��������");
		scanf("%d",list->elem+i);
		list->length++;
	}
}
void out(List *L,int m)
{
	int i=L->length,j;
	int mq=1,mp=0;
	int k[100]={0};
	int *p;
	p=L->elem;
	while(i!=0)
	{
		for(j=1;j<=m;j++)  //ѭ�����Ǹ��ˣ��Լ���ָ�뵽ĩβ����������ͷ 
		{
		while(k[mp]) mp++;
		p=L->elem+mp;
		mq=mp+1;
		if(mq>L->length){
			mp=0;
			while(k[mp]) mp++;
			p=L->elem+mp;
			mq=mp+1;
		}
    	mp=mq;
		}
		printf("%d:\t%d\n",L->length-i+1,*p);  //����Ǹ��� 
		k[mq-1]=1;
		i--;
	}
}
int main()
{
	List L;
	int n,m;
	system("date/t");
	system("time/t");
	printf("ѧ��:031720106\n����:����˳\n");
	InitList(&L);
	printf("�������Ȧ������:\n");
	scanf("%d",&n);
	printf("������ѭ�������������ٳ��У�\n");
	scanf("%d",&m);
	if(n==0) printf("��Ȧ������\n");
	else {
		createList(&L,n);
		out(&L,m);
	}
    return 0;
}
