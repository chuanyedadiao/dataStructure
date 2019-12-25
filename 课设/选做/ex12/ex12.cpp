#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct passenger
{
    char ID[20];//出生日期是,12,13位 
    char name[30];
    char num_flight[20];
    int year_flight;
    int month_flight;
    int day_flight;
    int miles;
    struct passenger *next;
}Passenger;

typedef struct
{
	int key;
	Passenger *next;
}LinkNode;

typedef struct
{
	LinkNode *base;
	int length;
}LinkList;

typedef struct
{
	Passenger *elem;
	int length;
	int listsize; 
}List;

void ClearString(char string[])
{
	int i=0;
	while(string[i]!='\0')
	{
		string[i]='\0';
		i++;
	}
}

int CreateLinkList(LinkList *list,FILE *in)
{
	Passenger *p;
	char ch;
	int i,keynum;
	int conflict=0;
	int mile,year,month,day;
	char date[2];
	char id[20]={'\0'},Name[30]={'\0'},Num_flight[30]={'\0'};
	list->base=(LinkNode *)malloc(31*sizeof(LinkNode));
	for(i=0;i<31;i++)
	{
		list->base[i].key=i+1;
		list->base[i].next=(Passenger*)malloc(sizeof(Passenger));
		list->base[i].next=NULL;
	}
	list->length=31;
	ch=fgetc(in);
	while(!feof(in))
	{
		i=0;
		while(ch!=' ')
		{
			id[i]=ch;
			ch=fgetc(in);
			i++;
		}//身份证 
		i=0;
		ch=fgetc(in);
		while(ch!=' ')
		{
			Name[i]=ch;
			ch=fgetc(in);
			i++;
		}//名字 
		i=0;
		ch=fgetc(in);
		while(ch!=' ')
		{
			Num_flight[i]=ch;
			ch=fgetc(in);
			i++;
		}//航班
		fscanf(in,"%d%d%d",&year,&month,&day);
		fscanf(in,"%d",&mile);
		date[0]=id[12];
		date[1]=id[13];//用身份证的出生日作为关键字 
		if(date[0]=='0') keynum=date[1]-48;
		else keynum=(date[1]-48)+(date[0]-48)*10;
		if(keynum>31)
		{
			printf("输入有误\n");
			exit(0);
		}
		p=(Passenger*)malloc(sizeof(Passenger));
        strcpy(p->ID,id);
        strcpy(p->name,Name);
        strcpy(p->num_flight,Num_flight);
        p->miles=mile;
        p->year_flight=year;
        p->month_flight=month;
        p->day_flight=day;//赋值，创建一个节点 
        if(list->base[keynum-1].next!=NULL) conflict++;//如果有重复的conflict++ 
        p->next=list->base[keynum-1].next;
        list->base[keynum-1].next=p;
        ClearString(id);
        ClearString(Name);
		ClearString(Num_flight); 
        ch=fgetc(in);//换行符
		ch=fgetc(in); 
	}
	return conflict;
}//链地址 

void output(LinkList linklist)
{
	Passenger *p;
	int i=0;
	while(i<linklist.length)
	{
		p=linklist.base[i].next;
		while(p)
		{
			printf("%s %s %s",p->ID,p->name,p->num_flight);
			printf("%d %d %d %d",p->year_flight,p->month_flight,p->day_flight,p->miles);
			p=p->next;
			printf("\n");
		}
		i++;
	}
}

int main()
{
	FILE *in;
	in=fopen("flight.txt","r");
	if(!in)
	{
		printf("Open flight.txt fail\n");
		exit(0);
	}
	LinkList linklist;
	CreateLinkList(&linklist,in);//链地址 
}
