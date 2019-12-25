#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10
typedef struct list
{
	int *elem; 
	int length;
	int listsize;
}List;
List InitList()
{
	List L;
	L.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!L.elem) 
	{
		printf("����˳���ʧ�ܣ�\n"); 
	    exit(0);
	}
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	printf("����˳���ɹ���\n");
	return L;
}
void createList(List *L,int n)
{
	int i;
	int *newbase;
	for(i=0;i<n;i++)
	{
		if(L->length>=L->listsize)
	{
		newbase=(int*)realloc(L->elem,(L->listsize+LISTINCERMENT)*sizeof(int));
		L->elem=newbase;
		L->listsize+=LISTINCERMENT;
	}
		printf("��������");
		scanf("%d",L->elem+i);
		L->length++;
	}
}
void reverse(List *L)
{
	int i,j;
	int t;
	i=0; j=L->length-1;
	for(;i<j;i++,j--)
	{
		t=*(L->elem+j);
		*(L->elem+j)=*(L->elem+i);
		*(L->elem+i)=t;
	}//���� 
}
void output(List *L)
{
	int i;
	for(i=0;i<L->length;i++)
	{
		printf("%d\t",*(L->elem+i));
	}
}
int main()
{
	List L;
	int n;
	system("date/t");
	system("time/t");
	printf("ѧ��:031720106\n����:����˳");
	L=InitList();
	printf("����˳�������ĸ�����\n");
	scanf("%d",&n);
	createList(&L,n);
	if(n==0) printf("��˳����ǿձ�");
	else{
		printf("����֮ǰ:\n");
	    output(&L);
	    reverse(&L);
	    printf("\n");
	    printf("����֮��\n");
	    output(&L);
	} 
	return 0;
}
