#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct bitnode 
{
	char KeyWords[80];
	char type[20];
	struct bitnode *Child;
	struct bitnode *Sibling;
}BiTNode,*BiTree;

typedef struct SearchWords
{
	char string[80];
}SearchWords;

typedef struct 
{
	SearchWords *base;
	int length;
}SearchList;


int n,m;

BiTree InitTree()
{
	BiTree T;
	T=(BiTree)malloc(sizeof(BiTNode));
	T->Child=NULL;
	T->Sibling=NULL;
	return T;
}//初始化树

void Getch(char *ch,FILE *in)
{
	(*ch)=fgetc(in);
	while(*ch==' '||*ch==',')
	{
		*ch=fgetc(in);
	}
}

void GetProperty(char Property[],FILE *in)
{
	int i=0;
	char ch,flag=' ';
	ch=fgetc(in);
	while(ch!='"')
	{
		if(ch=='\\')
		{
			flag=ch;
			ch=fgetc(in);
			if(!(ch=='"'||ch=='\\'))
			{
				printf("输入有误");
				exit(0);
			}
			Property[i]=ch;
		}
		Property[i]=ch;
		i++;
		ch=fgetc(in);
		flag=' ';
	}
}

void ClearString(char string[])
{
	int i=0;
	while(string[i]!='\0')
	{
		string[i]='\0';
		i++;
	}
} 

BiTNode *CreateString(BiTNode *p1,FILE *in)
{
	BiTNode *q;
	char value[80];
	q=(BiTNode*)malloc(sizeof(BiTNode));
	GetProperty(value,in);
	q->Child=NULL;
	q->Sibling=NULL;
	strcpy(q->KeyWords,value);
	p1->Child=q;
	return p1;
}

int CreateObject(BiTNode **Root,FILE *in,int i,int n)
{
	char ch1,ch2;
	char Property[80];//键对中的“键”的部分由property表示 
	BiTNode *Childs;
	BiTNode *q1,*q2;
	int cnt;
	Getch(&ch1,in);
	cnt=i;
	while(cnt<=n&&ch1!='}')
	{
	    if(ch1=='\n'){
			cnt++;
			if(cnt<=n) Getch(&ch1,in);//读取下一行的字符 
			continue;
	    }
		GetProperty(Property,in);
		Getch(&ch2,in);//得到冒号 
		Getch(&ch1,in);//观察得到的是{还是“ 
		if(ch1=='"')
		{
			q2=(BiTNode *)malloc(sizeof(BiTNode));
			q2->Child=NULL;
			q2->Sibling=NULL;
			strcpy(q2->KeyWords,Property);
			q2=CreateString(q2,in);
			strcpy(q2->type,"STRING");
			q2->Sibling=(*Root)->Child;
			(*Root)->Child=q2;
		}
		if(ch1=='{'){
			q2=(BiTNode *)malloc(sizeof(BiTNode));
			q2->Child=NULL;
			q2->Sibling=NULL;
			strcpy(q2->KeyWords,Property);
			cnt=CreateObject(&q2,in,cnt,n);
			strcpy(q2->type,"OBJECT");
			q2->Sibling=(*Root)->Child;
			(*Root)->Child=q2;
		}
		Getch(&ch1,in); 
		ClearString(Property);
	}
	return cnt;
}

BiTree CreateTree(BiTree T,FILE *in)
{
	int i=1;
	char ch1,ch2,flag;
	Getch(&ch2,in);
	Getch(&ch1,in);
	while(i<=n)
	{
		if(ch1=='\n') i++;
		if(ch1=='{'){
			i=CreateObject(&T,in,i,n);
		}
	}
	return T;
}

void InitSearchList(SearchList *Slist,FILE *in)
{
	Slist->base=(SearchWords*)malloc(m*sizeof(SearchWords));
	Slist->length=m;
	int i=0,j;
	char ch;
	for(i=0;i<m;i++)
	{
		ch=fgetc(in);
		j=0;
		while(ch!='\n')
		{
		    (Slist->base+i)->string[j]=ch;
			ch=fgetc(in);
			j++;	
		}
		(Slist->base+i)->string[j]='\0';
	}
}

int JudgeDot(char search[],char father[],char son[])
{
	int i=0,j;
	while(search[i]!='\0')
	{
		if(search[i]=='.')
		{
			strncpy(father,search,i);
			j=i+1;
			while(search[j]!='\0')
			{
				j++;
			}
			strncpy(son,&(search[i+1]),j-i-1);
			son[j-i-1]='\0';
			return 1;
		}
		i++;
	}
	return 0;
}

int SearchInTree(char search[],char result[],BiTree T,BiTNode **flag)
{
	if(T==NULL)
	{
		*flag=NULL;
		return 0;
	}
	if(strcmp(search,T->KeyWords)==0&&strcmp("STRING",T->type)==0)
	{
		strcpy(result,T->Child->KeyWords);
		*flag=T;
		return 1;
	}
	else
	{
		if(strcmp(search,T->KeyWords)==0&&strcmp("OBJECT",T->type)==0)
		{
			*flag=T;
			return 2;
		}
		else 
		{
			SearchInTree(search,result,T->Sibling,flag);
		}
	} 
	
}

int SearchInObject(char search[],char result[],BiTNode *p)
{
	int tag=-1;
	BiTNode *q;
	char father[80],son[80];
	if(!JudgeDot(search,father,son))
	{
		tag=SearchInTree(search,result,p,&q);
		return tag;
	}
	else{
		tag=SearchInTree(father,result,p,&q);
		if(tag==0)
		{
			return tag;
		}
		tag=SearchInObject(son,result,q->Child);
	}
	return tag;
}

void Search(SearchList *Slist,BiTree T)
{
	BiTNode *p;
	p=T->Child;
	int i,tag=-1;
	int judge=0;
	char out[80],father[80],son[80];
	for(i=0;i<Slist->length;i++)
	{
		if(!JudgeDot((Slist->base+i)->string,father,son))
		{
			tag=SearchInTree((Slist->base+i)->string,out,T->Child,&p);
			if(tag==1) printf("STRING %s\n",out);
			else if(tag==2) printf("OBJECT\n");
			else if(tag==0) printf("NOTEXIST\n");
		}
		else 
		{
			tag=SearchInTree(father,out,T->Child,&p);
			if(tag==0) printf("NOTEXIST\n");
			else 
			{
				tag=SearchInObject(son,out,p->Child);
				if(tag==1) printf("STRING %s\n",out);
				else if(tag==2) printf("OBJECT\n");
				else if(tag==0) printf("NOTEXIST\n");
			}
			ClearString(father);
			ClearString(son);
		}
		ClearString(out);
		tag=-1;
		p=T->Child;
	}
}

int main()
{
    FILE *in;
    SearchList Slist;
	in=fopen("Input.txt","r");
	if(in==NULL)
	{
		printf("Can't open the file Input.txt\n");
		exit(0);
	}
	fscanf(in,"%d%d",&n,&m);
	BiTree T;
	T=InitTree();
	T=CreateTree(T,in);
	InitSearchList(&Slist,in);
	Search(&Slist,T);
	return 0;
}
