#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	int *key;
	int length;
}Keys;

typedef struct
{
	int key_num;
	int start_time;
	int end_time;
}Classes;

typedef struct 
{
	Classes *base;
	int length;
}Class_List;

typedef struct  QNode
{
	Classes data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct Link
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitKeys(Keys *keys,int N)
{
	keys->key=(int *)malloc(N*sizeof(int));
	if(!keys->key)
	{
		printf("创建失败\n");
		exit(0);
	}
	keys->length=N;
	int i;
	for(i=0;i<N;i++)
	{
		*(keys->key+i)=i+1;
	}
}

void InitClassList(Class_List **classlist,int K)
{
	(*classlist)->base=(Classes *)malloc(K*sizeof(Classes));
	if(!(*classlist)->base)
	{
		printf("创建失败\n");
		exit(0);
	} 
	(*classlist)->length=K;
}

Keys Input(int *N,int *K,Class_List *classlist)
{
	FILE *in;
	int i;
	in=fopen("Input.txt","r");
	if(in==NULL)
	{
		printf("Can't open the file Input.txt\n");
		exit(0);
	}//从文件中读入
	fscanf(in,"%d%d",N,K);
	Keys keys;
	int during_time;
	InitKeys(&keys,*N);
	InitClassList(&classlist,*K);
	for(i=0;i<*K;i++)
	{
		fscanf(in,"%d%d%d",&classlist->base[i].key_num,&classlist->base[i].start_time,&during_time); 
        classlist->base[i].end_time=classlist->base[i].start_time+during_time;
	}
	fclose(in);
	return  keys;
}

void InitQueue(LinkQueue *Q)
{
	Q->front=(QueuePtr)malloc(sizeof(QNode));
	Q->rear=Q->front;
	Q->front->next=NULL;
}//创建队列 

void EnQueue(LinkQueue *Q,Classes e)
{
	QNode *p;
	p=(QNode*)malloc(sizeof(QNode));
	Q->rear->next=p;
	p->data=e;
	Q->rear=p;
	p->next=NULL;
}

void DeQueue(LinkQueue *Q,Classes *e)
{
	if(Q->front==Q->rear)
	{
		printf("该队列为空");
		return ;
	}
	QNode *p,*q;
	p=Q->front->next;
	*e=p->data;
	q=p->next;
	Q->front->next=q;
	if(Q->rear==p) Q->rear=Q->front;
	free(p);
}

int ExsitQueue(LinkQueue *Q,Classes flag)
{
	QNode *p,*q;
	p=Q->front;
	q=p->next;
	while(q)
	{
		if(flag.key_num=q->data.key_num&&flag.start_time==q->data.start_time&&flag.end_time==q->data.end_time)
		    return 1;
		p=q;
		q=p->next;
	}
	return 0;
}

void InitStartQueue(LinkQueue *Q,Class_List classlist)
{
	int i,j;
	int min_StartTime;
	int max_StartTime=0;
	Classes flag;
	for(i=0;i<classlist.length;i++)
	{
		if(classlist.base[i].start_time>max_StartTime)
		{
			max_StartTime=classlist.base[i].start_time;
		}
	}
	for(i=0;i<classlist.length;i++)
	{
		min_StartTime=max_StartTime;
		for(j=0;j<classlist.length;j++)
		{
			if(!ExsitQueue(Q,classlist.base[j])&&classlist.base[j].start_time<=min_StartTime)
			{
				flag=classlist.base[j];
				min_StartTime=classlist.base[j].start_time;
			}
		}
		EnQueue(Q,flag);
	}
}

void InitEndQueue(LinkQueue *Q,Class_List classlist)
{
	int i,j;
	int min_EndTime;
	int max_EndTime=0;
	Classes flag1,flag2;
	for(i=0;i<classlist.length;i++)
	{
		if(classlist.base[i].end_time>max_EndTime)
		{
			max_EndTime=classlist.base[i].end_time;
			flag2=classlist.base[i];
		}
	}
	for(i=0;i<classlist.length;i++)
	{
		min_EndTime=max_EndTime;
		flag1=flag2;
		for(j=0;j<classlist.length;j++)
		{
			if(!ExsitQueue(Q,classlist.base[j])&&classlist.base[j].end_time<=min_EndTime)
			{
				if(classlist.base[j].end_time==min_EndTime&&classlist.base[j].key_num>flag1.key_num)
				{
			        continue;
				}
				flag1=classlist.base[j];
				min_EndTime=classlist.base[j].end_time;
			}
		}
		EnQueue(Q,flag1);
	}
}

void GetHead(LinkQueue *Q,Classes *e)
{
	if(Q->front==Q->rear)
	{
		return; 
	}
	QNode *p;
	p=Q->front->next;
	*e=p->data;
} 

int QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear){
		return 1;
	}
	else return 0;
}

Keys *ReturnKeys(Keys *keys,Classes end)
{
	int i=0;
	while(i<keys->length)
	{
		if(keys->key[i]==-1)
		{
			keys->key[i]=end.key_num;
			break;
		}
		i++;
	}
	return keys;
}

Keys *TakeKeys(Keys *keys,Classes start)
{
	int i=0;
	while(i<keys->length)
	{
		if(keys->key[i]==start.key_num)
		{
			keys->key[i]=-1;
			break;
		}
		i++;
	}
	return keys;
}

void OutPutKeyList(Keys *keys) 
{
	int i=0;
	while(i<keys->length)
	{
		printf("%d ",keys->key[i]);
		i++;
	}
}

void ChangeKeys(Class_List *classlist,Keys *keys)
{
	LinkQueue StartSortQueue,EndSortQueue;
	InitQueue(&StartSortQueue);
	InitQueue(&EndSortQueue);
	InitStartQueue(&StartSortQueue,*classlist);
	InitEndQueue(&EndSortQueue,*classlist);
	int time=1;
	Classes start,end;
	GetHead(&EndSortQueue,&end);
	while(!QueueEmpty(StartSortQueue))
	{
		DeQueue(&StartSortQueue,&start);
		time=start.start_time;
		while(end.end_time<=time)
		{
			keys=ReturnKeys(keys,end);
			DeQueue(&EndSortQueue,&end);
			GetHead(&EndSortQueue,&end);
		}//先还完所有的钥匙 
		keys=TakeKeys(keys,start);//再取钥匙
	}
	while(!QueueEmpty(EndSortQueue))
	{
		keys=ReturnKeys(keys,end);
		DeQueue(&EndSortQueue,&end);
		GetHead(&EndSortQueue,&end);
	}
	OutPutKeyList(keys);
}

int main()
{
	int N,K;
	Keys keys;
	Class_List classlist;
	keys=Input(&N,&K,&classlist);
	ChangeKeys(&classlist,&keys);
	return 0;
}
