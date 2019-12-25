#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10
typedef struct List
{
	int *elem;
	int length;
	int listsize;
}Sqlist;
void InitList(Sqlist *list)
{
	list->elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!list->elem) 
	{
		printf("创建顺序表失败！"); 
	    exit(0);
	}
	list->length=0;
	list->listsize=LIST_INIT_SIZE;
	printf("创建顺序表成功！");
}
void DestroyList(Sqlist *list)
{
	free(list->elem);
	list->length=0;
	list->listsize=0;
}
void clearList(Sqlist *list)
{
	list->length=0;
}
int isEmpty(Sqlist p)
{
	if(p.length==0)
	return 1;
	else return 0;
}
int Listlength(Sqlist p)
{
	return p.length;
}
void Getelem(Sqlist p,int i,int *e)
{
	if(i<1||i>p.length) {
		printf("顺序表中无该位置\n");
		return;
	}
	else 
	{
	*e=*(p.elem+i-1);
	printf("你想找到的第%d数据为%d.",i,*e);
    }
}
int LocalElem(Sqlist p,int e)
{
	bool judge=0;
	int i=0,j;
	for(;i<p.length;i++)
	{
		if(e==*(p.elem+i))
		{
			judge=1;
			j=i;
			break;
		}
	} 
	if(judge==1) return i+1;
	else return 0;
}
void priorElem(Sqlist p,int cur_e,int* pre_e)
{
	int i=0;
	bool judge=0;
	for(;i<p.length;i++)
	{
		 if(cur_e==*(p.elem+i+1)){
		 	judge=1;
		 	*pre_e=*(p.elem+i);
		 	break;
		 }
	}
	if(!judge){
	printf("pre_e不存在，操作失败");
	} 
	else 	printf("该数据前一位数据为%d.\n",*pre_e);
}
void NextElem(Sqlist p,int cur_e,int* next_e)
{
	int i;
	bool judge=0;
	for(i=0;i<p.length-1;i++)
	{
		if(cur_e==*(p.elem+i)){
			judge=1;
			*next_e=*(p.elem+i+1);
			break;
		}
	}
	if(!judge) printf("next_e不存在，操作失败");
	else 			printf("该数据后一位数据为%d.\n",*next_e);
}
void ListInsert(Sqlist *list,int i,int e)
{
	int* newbase;
	int *m,*q;
	if(i<1||i>list->length+1) return;
	if(list->length>=list->listsize)
	{
		newbase=(int*)realloc(list->elem,(list->listsize+LISTINCERMENT)*sizeof(int));
		list->elem=newbase;
		list->listsize+=LISTINCERMENT;
	}
	q=list->elem+i-1;
	m=list->elem+list->length-1;
	for(;q<=m;m--) *(m+1)=*(m);
	*q=e;
	list->length++;
}
void ListDelete(Sqlist *list,int i,int *e)
{
	if(i<1||i>list->length) return;
	int *m;
	m=list->elem+i-1;
	e=m;
	for(;m<list->elem+list->length-1;m++) *m=*(m+1);
	list->length--;
}
void visit(int *p)
{
	printf("%d\t",*p);
}
void ListTraverse(Sqlist p)
{
	int i=0;
	for(;i<p.length;i++)
	{
		visit(p.elem+i);
	}
}
void createList(Sqlist *list,int n)
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
		printf("输入数：");
		scanf("%d",list->elem+i);
		list->length++;
	}
}

int main()
{
	Sqlist L;
	int m=-1,n;
	int judge,length,ele,i;
	int pre_e,next_e;
	while(m!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺");
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
	printf("13.createList\n");
	printf("0.exit\n");
	scanf("%d",&m);
	switch(m)
	{
		case 1:{
			system("cls");
			InitList(&L);
			printf("已成功创建顺序表\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyList(&L);
			printf("已成功销毁了顺序表\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			clearList(&L);
			printf("成功清空了顺序表\n");
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			judge=isEmpty(L);
			if(judge==1) printf("该顺序表为空表\n");
			else printf("该顺序表不是空表\n"); 
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			length=Listlength(L);
			printf("当前顺序表的长度为%d.",length);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			printf("请输入你想找到数据的位置：\n");
			scanf("%d",&i);
			Getelem(L,i,&ele);
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			printf("请输入你想在顺序表中找到的数据：\n");
			scanf("%d",&ele);
			i=LocalElem(L,ele);
			if(i) printf("ele在顺序表中的第%d位.\n",i);
			else printf("ele不在该顺序表中."); 
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
			ListInsert(&L,i,ele);
			printf("加入数据成功！\n");	
			system("pause");
			break;
		}
		case 11:{ 
			system("cls");
			printf("请输入你想删除的数据以及其位置？\n");
			scanf("%d%d",&ele,&i);
			ListDelete(&L,i,&ele);
			printf("该数据删除成功\n"); 
			printf("删除的数据是第%d位的%d\n",i,ele); 
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
			printf("请输入你想输入的数的个数：");
			scanf("%d",&n);
			createList(&L,n);
			printf("创建成功\n");
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
