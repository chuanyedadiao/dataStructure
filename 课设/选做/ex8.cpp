#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

int N,M;

typedef struct Clubfriend
{
	int keynum;
	struct Clubfriend *next;
}Clubfriend;

typedef struct 
{
	int key;
	Clubfriend *next;
}Student;

typedef struct
{
	Student *base;
	int length;
}StudentsList;

typedef struct 
{
	int *studentNum;
	int length;
}StudentNode;

typedef struct
{
	int club;
	StudentNode clubStudent;
}Club;

typedef struct 
{
	Club *base;
	int length;
}ClubList;

void CreateStudentNode(StudentNode *studentnode,int nodelength)
{
	int i=0;
	studentnode->studentNum=(int*)malloc(nodelength*sizeof(int));
	while(i<nodelength)
	{
		scanf("%d",studentnode->studentNum+i);
		i++;
	}
	studentnode->length=nodelength;
}

void CreateClub(ClubList *clublist)
{
	clublist->base=(Club*)malloc(M*sizeof(Club)); 
	int i=0,j;
	int nodelength;
	while(i<M)
	{
		clublist->base[i].club=i+1;
		scanf("%d",&nodelength);
		CreateStudentNode(&(clublist->base[i].clubStudent),nodelength);
		i++;
	}
	clublist->length=M;
}

int ExistInStudent(Student m,int e)
{
	Clubfriend *p;
	p=m.next;
	while(p)
	{
		if(p->keynum==e)
		    return 1;
		p=p->next;
	}
	return 0;
}

void CreateFriends(Student *student,ClubList clublist)
{
	int i,k,j=0;
	StudentNode p;
	Clubfriend *q;
	for(;j<clublist.length;j++)
	{
		p=clublist.base[j].clubStudent;
		for(i=0;i<p.length;i++)
		{
			if(p.studentNum[i]==student->key)
			{
				break;
			}
		}
		if(i!=clublist.base[j].clubStudent.length)
		{
			k=0;
			while(k<clublist.base[j].clubStudent.length)
			{
				if(k==i||ExistInStudent(*student,p.studentNum[k]))
				{
					k++;
					continue;
				}
				q=(Clubfriend*)malloc(sizeof(Clubfriend));
				q->keynum=*(clublist.base[j].clubStudent.studentNum+k);
		        q->next=student->next;
		        student->next=q;
		        k++;
			}
		}
	}
}

StudentsList *Add(StudentsList *list,int i,int e)
{
	Student s=list->base[e-1];
	Clubfriend *p,*q;
	p=s.next;
	while(p)
	{
		if(p->keynum==list->base[i].key||ExistInStudent(list->base[i],p->keynum))
		{
			p=p->next;
			continue;
		}//如果存在这个朋友或者这个num等于自己，跳过 
	    q=(Clubfriend*)malloc(sizeof(Clubfriend));
	    q->keynum=p->keynum;
	    q->next=list->base[i].next;
	    list->base[i].next=q;
	    p=p->next;
	}
	return list;
}

StudentsList *Extrafriend(StudentsList *list,int i)
{
	Clubfriend *p;
	p=list->base[i].next;
	while(p)
	{
		list=Add(list,i,p->keynum);
		p=p->next;
	}
	return list;
}

void CreateStudentList(StudentsList *list,ClubList clublist)
{
	int num,max=0;
	list->base=(Student*)malloc(N*sizeof(Student));
	int i=0;
	while(i<N)
	{
		list->base[i].key=i+1;
		list->base[i].next=(Clubfriend*)malloc(sizeof(Clubfriend));
		list->base[i].next=NULL;
		i++;
	}
	list->length=N;
	for(i=0;i<list->length;i++)
	{
		CreateFriends(&list->base[i],clublist);
	}
	for(i=0;i<list->length;i++)
	{
		list=Extrafriend(list,i);
	}
}

int Traverse(Student m)
{
	Clubfriend *p;
	int i=0;
	p=m.next;
	while(p)
	{
		i++;
		p=p->next;
	}
	return i;
}

int main()
{
	ClubList clublist;
	StudentsList list;
	scanf("%d%d",&N,&M);
	CreateClub(&clublist);
	CreateStudentList(&list,clublist); 
	int i=0,max=0,nums;
	for(i=0;i<list.length;i++)
	{
		nums=Traverse(list.base[i])+1;//加上自己 
		if(nums>max) max=nums;
	}
	printf("%d",max);
}

/*
7 4
3 1 2 3
2 1 4
3 5 6 7
1 6 



7 4
4 1 2 3 5
2 1 4
3 5 6 7
1 6
*/
