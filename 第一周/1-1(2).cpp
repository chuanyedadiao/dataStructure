#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct lnode
{
	int data;
	struct lnode *next;
}LNode,*LinkList;
LinkList InitList()
{
	LinkList L;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	return L;
}
void DestroyList(LinkList L)
{
	LNode *p,*q;
	if(L->next==NULL) {
		free(L);
		return;
	}
	else {
	p=L;
	q=p->next;
	while(q)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
}
}
void clearList(LinkList list)
{
	LNode *p;
	p=list;
	p->next=NULL;
}
int isEmpty(LinkList list)
{
	LNode *p;
	p=list->next;
	if(p==NULL) return 1;
	else return 0; 
}
int Listlength(LinkList list)
{
	int i=0;
	LNode *p,*q;
	p=list;
	q=p->next;
	while(q!=NULL)
	{
		i++;
		p=q;
		q=p->next;
	}
	return i;
}
int Getelem(LinkList list,int i,int *e)
{
	LNode *p;
	p=list;
	while(i)
	{
		if(p==NULL){
			printf("没有该数据！\n");
			return 0;
		}
		p=p->next;
		i--;
	}
	*e=p->data;
	return 1;
} 
int LocalElem(LinkList list,int e)
{
	LNode *p,*q;
	int i=0;
	p=list;
	q=p->next;
	while(q)
	{
		if(p->data==e)
		{
			return i;
		}
		i++;
		p=q;
		q=p->next;
	}
	if(p->data==e)
		{
			return i;
		}
    else return 0;
}
void priorElem(LinkList list,int cur_e,int *pre_e)
{
	LNode *p,*q;
	p=list;
	q=p->next;
	if(q==NULL||q->data==cur_e)
	{
		printf("操作无意义，pre_e无定义\n");
	}
	else {
		p=q;
		q=p->next;
    	while(q)
	   {
	   if(q->data==cur_e) {
	   *pre_e=p->data;
	   printf("前一位数据为：%d\n",*pre_e);
	   break;
	   }
	   p=q;
	   q=p->next;
	   }	
	}	
}
void NextElem(LinkList list,int cur_e,int *next_e)
{
	LNode *p,*q;
	bool judge=0;
	p=list;
	q=p->next;
	while(q)
	{
		if(p->data==cur_e){
			*next_e=q->data;
			judge=1;
			break;
		}
		p=q;
		q=p->next;
	}
	if(!judge) printf("操作无意义，next_e无定义\n");
	else printf("后一位数据为：%d\n",*next_e);
} 
void ListInsert(LinkList list,int i,int e)
{
	LNode* p,* q,*s;
	int j=1;
	p=list;
	q=p->next;
	while(j<i)
	{
		p=q;
		q=p->next;
		j++;
	}
	s=(LNode *)malloc(sizeof(LNode));
	s->next=q;
	p->next=s;
	s->data=e;
}
void ListDelete(LinkList list,int i,int *e)
{
	LNode *p,*q;
	int j=i;
	p=list;
	q=p->next;
	while(q!=NULL&&(i-1)!=0)
	{
		p=q;
		q=p->next;
		i--;
	}
	if(q!=NULL){
	*e=q->data;
	p->next=q->next;
	free(q);
    }
	else printf("链表中未找到第%d位数据",j);
}
void visit(int m)
{
	printf("%d\t",m);
} 
void ListTraverse(LinkList list)
{
	LNode *p,*q;
	p=list;
	q=p->next;
	bool judge=1;
	while(q)
	{
        visit(q->data);
		p=q;
		q=p->next;
	}
}
void createList(LinkList list,int n)
{
	LNode *p,*q;
	p=list;
	int i;
	for(i=0;i<n;i++)
	{
	    q=(LNode *)malloc(sizeof(LNode));
		p->next=q;
		printf("输入数据\n");
		scanf("%d",&q->data);
		p=q;
	}
	p->next=NULL;
}
int main()
{
	LinkList L;
	int m=-1,n;
	int length;
	bool judge;
	int ele;
	int i;
	int pre_e,next_e;
	while(m!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺");
	printf("请输入需要进行的操作：\n");
	printf("请输入需要进行的操作：\n");
	printf("1.InitList\n");
	printf("2.DeleteList\n");
	printf("3.ClearList\n");
	printf("4.isEmpty\n");
	printf("5.ListLength\n");
	printf("6.GetElem\n");
	printf("7.LocalElem\n");
	printf("8.prior_elem\n");
	printf("9.next_elem\n");
	printf("10.ListInsert\n");
	printf("11.ListDelete\n");
	printf("12.ListTracverse\n");
	printf("13.CreatList\n"); 
	printf("0.exit\n");
	scanf("%d",&m);
	switch(m)
	{
		case 1:{
			system("cls");
			L=InitList();
			printf("已成功创建链表\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyList(L);
			printf("已成功销毁了链表\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			clearList(L);
			printf("成功清空了链表\n");
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			judge=isEmpty(L);
			if(judge==1) printf("该链表为空表\n");
			else printf("该链表不是空表\n"); 
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			length=Listlength(L);
			printf("当前链表的长度为%d.",length);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			printf("请输入你想找到数据的位置：\n");
			scanf("%d",&i);
			judge=Getelem(L,i,&ele);
			if(judge)
			printf("你想找到的第%d数据为%d.",i,ele);
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			printf("请输入你想在链表中找到的数据：\n");
			scanf("%d",&ele);
			i=LocalElem(L,ele);
			if(i) printf("ele在链表中的第%d位.\n",i);
			else printf("ele不在该链表中."); 
			system("pause");
			break;
		}
		case 8:{ 
			system("cls");
			printf("请输入你想找到哪个数据的前一位数据：\n");
			scanf("%d",&ele);
			priorElem(L,ele,&pre_e);
			system("pause");
			break;
		}
		case 9:{ 
			system("cls");
			printf("请输入你想找到哪个数据的后一位数据：\n");
			scanf("%d",&ele);
			NextElem(L,ele,&next_e);
			system("pause");
			break;
		}
		case 10:{ 
			system("cls");
		    printf("请输入你想插入该数据到哪一位置？\n");
			scanf("%d%d",&ele,&i);
			ListInsert(L,i,ele);
			printf("加入数据成功！\n");	
			system("pause");
			break;
		}
		case 11:{ 
			system("cls");
			printf("请输入你想删除的数据以及其位置？\n");
			scanf("%d%d",&ele,&i);
			ListDelete(L,i,&ele);
			printf("该数据删除成功\n"); 
			printf("删除的数据为第%d位的%d\n",i,ele);
			system("pause");
			break;
		}
		case 12:{ 
			system("cls");
			printf("该顺序表里面的数据有\n");
			ListTraverse(L); 
			printf("\n");
			system("pause");
			break;
		}
		case 13:{
			system("cls");
			printf("创建链表\n");
			printf("输入初始数据总数\n");
			scanf("%d",&n);
			createList(L,n);
			system("pause");
			break;
		}
		case 0:{
			printf("已成功退出！\n");
			exit(0);
			break;
		}
	}
	}
	return 0;
}
