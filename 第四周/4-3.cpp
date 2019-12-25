#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10
#define LIST_START_SIZE 100
typedef struct start
{
	int *data;
	int length;
	int listsize;
}Start;

typedef struct {
	int num;
	bool judge;
}Seat;

typedef struct List
{
	Seat *elem;
	int length;
	int listsize;
}Sqlist;

void Initstart(Start *start)
{
	start->data=(int *)malloc(LIST_START_SIZE*sizeof(int));
	if(!start->data) 
	{
		printf("创建起始位置失败！"); 
	    exit(0);
	}
	start->length=0;
	start->listsize=LIST_START_SIZE;
}

void InitList(Sqlist *list)
{
	list->elem=(Seat *)malloc(LIST_INIT_SIZE*sizeof(Seat));
	if(!list->elem) 
	{
		printf("创建顺序表失败！"); 
	    exit(0);
	}
	list->length=0;
	list->listsize=LIST_INIT_SIZE;
}

void createList(Sqlist *list)
{
	int i;
	Seat *newbase;
	for(i=0;i<100;i++)
	{
		if(list->length>=list->listsize)
	{
		newbase=(Seat*)realloc(list->elem,(list->listsize+LISTINCERMENT)*sizeof(Seat));
		list->elem=newbase;
		list->listsize+=LISTINCERMENT;
	}
		(list->elem+i)->num=i+1; 
		(list->elem+i)->judge=0;
		list->length++;
	}
}

int Find_Start(Sqlist *list,int e)
{
	int i,found=0;
	Seat *p=list->elem,*begin;
	begin=p;
	while(p-list->elem!=100)
	{
		for(i=0;i<e;i++)
		{
			if(p->judge){
				break;
			}
			if(p->num%5==0){
				break;
			}//首先找连坐的位置 
			p++;
		}
		if(i==e||p-begin+1==e&&!p->judge){
		    found=1;
			break;	
		}
		else{
			p++;
			begin=p;
		}
	}
	if(found) return begin-list->elem;
	else return -1;//若是-1的话，就没有连坐的位置，找数值小的位置坐下 
}

void Find_Seat(int a[],int n,Sqlist *list,Start *S)
{
	int i,j;
	int m;
	Seat *p=list->elem;
	for(i=0;i<n;i++)
	{
		m=Find_Start(list,a[i]);
		*(S->data+i)=m;
		if(m!=-1){
			for(j=m;j<a[i]+m;j++){
				(list->elem+j)->judge=1;
				printf("%d   ",(list->elem+j)->num);
			}
		}
		else if(m==-1){
			for(j=0;j<a[i];p++){
				if(p->judge!=1){
					p->judge=1;
					printf("%d   ",p->num);
					j++;
				}
			}
		}
		printf("\n");
	}
}
void InitTickets(int n,int a[])
{
	int i;
	printf("Please input the tickets needed:\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
}
void JudgeTickets(int n,int a[])
{
	int i,j;
	int total=0;
	for(i=0;i<n;i++)
	{
		if(a[i]>5) {
			printf("一个人所购买的票不能超过五张，请重新输入\n");
			InitTickets(n,a);
			return;
		}
		total+=a[i];
	}
	if(total>100){
		printf("所购买的票超过总座位数，请重新输入\n");
		InitTickets(n,a);
		return ;
	}
}
int main()
{
	Sqlist L;
	Start S;
	int i,n,a[100]={0};
	printf("Please Input n:\n");
	scanf("%d",&n);
	InitTickets(n,a);
	JudgeTickets(n,a);
	InitList(&L);
	Initstart(&S);
	createList(&L);
	Find_Seat(a,n,&L,&S);
	return 0;
}
