#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10

typedef struct {
	int *base;
	int length;
	int listsize;
}Hnode;

typedef struct{
	int frequency;
	char str;
	Hnode node;
	int parent,lchild,rchild;
}HTNode;

typedef struct{
	HTNode *base;
	int LeafLength;
	int TotalLength;
	int Maxsize;
}HuffmanTree;

void ExsitInHuffmanTree(HuffmanTree **HT,char ch,int *flag)
{
	int i;
	for(i=0;i<(*HT)->LeafLength;i++)
	{
		if(ch==((*HT)->base+i)->str)
		{
			((*HT)->base+i)->frequency++;
			*flag=1;
			return;
		}
	}
	*flag=0;
}

void InitHuff(HuffmanTree **HT)
{
	(*HT)->base=(HTNode *)malloc(LIST_INIT_SIZE*sizeof(HTNode));
	(*HT)->LeafLength=0;
	(*HT)->TotalLength=0;
	(*HT)->Maxsize=LIST_INIT_SIZE;
}

void InsertHuffmanTree(HuffmanTree **HT,char leaf)
{
	HTNode *newbase;
	HTNode *p;
	if((*HT)->LeafLength>=(*HT)->Maxsize)
	{
		newbase=(HTNode *)realloc((*HT)->base,((*HT)->Maxsize+LISTINCERMENT)*sizeof(HTNode));
		(*HT)->base=newbase;
		(*HT)->Maxsize+=LISTINCERMENT;
	}
	p=((*HT)->base+(*HT)->LeafLength);
	p->lchild=-1;
	p->rchild=-1;
	p->parent=-1;
	p->str=leaf;
	p->frequency=1;
	p->node.base=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	p->node.length=0;
	p->node.listsize=LIST_INIT_SIZE;
	(*HT)->LeafLength++;
}

void Select(HuffmanTree HT,int *s1,int *s2,int i)
{
	int j,min1,min2;
	HTNode *p;
	p=HT.base;
	min1=2000;
	min2=2000;
	for(j=0;j<i;p++,j++)
	{
		if(p->parent==-1&&min1>p->frequency)
		{
			min1=p->frequency;
			*s1=j;
		}
	}
	p=HT.base;
	for(j=0;j<i;p++,j++)
	{
		if(p->parent==-1&&min2>p->frequency&&j!=*s1)
		{
			min2=p->frequency;
			*s2=j;
		}
	}
}

void ExtendSpace(HuffmanTree **HT)
{
	HTNode *newbase;
	if((2*(*HT)->LeafLength-1)>=(*HT)->Maxsize)
	{
		newbase=(HTNode *)realloc((*HT)->base,(2*(*HT)->LeafLength-1)*sizeof(HTNode));
		(*HT)->base=newbase;
		(*HT)->Maxsize=(2*(*HT)->LeafLength-1);
	}
	int i=(*HT)->LeafLength;
	(*HT)->TotalLength=(2*(*HT)->LeafLength-1);
	HTNode *p;
	p=(*HT)->base;
	while(i<(*HT)->TotalLength)
	{
		(p+i)->parent=-1;
		(p+i)->lchild=-1;
		(p+i)->rchild=-1;
		(p+i)->node.base=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
		(p+i)->node.length=0;
		(p+i)->node.listsize=LIST_INIT_SIZE;
		i++;
	}
}

void CreateHuffmanTree(HuffmanTree *HT,FILE *Input)
{
	char ch;
	int t;
	int tag=0,i,m;
	int s1,s2;
	InitHuff(&HT);
	HTNode *p; 
	ch=fgetc(Input);
	while(!feof(Input))
	{
		ExsitInHuffmanTree(&HT,ch,&tag);//如果存在，就frequency++ 
		if(tag==0)
		{
			InsertHuffmanTree(&HT,ch);//不存在就插入一个新的叶子 
		}
		ch=fgetc(Input);
	}//输入所有的字符
	ExtendSpace(&HT);//扩大Huffman的空间 
	p=HT->base;
	m=2*(HT->LeafLength)-1;
	for(i=HT->LeafLength;i<m;i++)
	{
		Select(*HT,&s1,&s2,i);//挑选出最小的两个值 
		if(s1>s2)
		{
			t=s1;
			s1=s2;
			s2=t;
		}
		(p+s1)->parent=i;
		(p+s2)->parent=i;
		(p+i)->lchild=s1;//小的那个值赋给左子树 
		(p+i)->rchild=s2;
		(p+i)->frequency=(p+s1)->frequency+(p+s2)->frequency;//构建huffman树 
	}
}

HTNode *InsertCode(HTNode *p,int e)
{
	int m;
	m=p->node.length;
	int *newbase;
	if(p->node.length>=p->node.listsize)
	{
		newbase=(int *)realloc(p->node.base,(p->node.listsize+LISTINCERMENT)*sizeof(int));
		p->node.base=newbase;
		p->node.listsize+=LISTINCERMENT;
	}
	*((p->node.base)+m)=e;
	(p->node.length)++;
	return p;
}

HTNode *CopyNode(HTNode *father,HTNode *son)
{
	int *f,*s;
	f=father->node.base;
	s=son->node.base;
	int i=0;
	while(i<father->node.length)
	{
		*(s+i)=*(f+i);
		son->node.length++;
		i++;
	}
	return son;
}

void CreateCode(HuffmanTree *HT,int point)
{
	HTNode *p,*q;
	p=(HT->base+point);
	if(p->lchild==-1&&p->rchild==-1)//若是叶子了就退出 
	{
		return;
	}
	else{
		q=(HT->base+p->lchild);
		q=CopyNode(p,q);//将其父类的编码给到子类 
		q=InsertCode(HT->base+p->lchild,48);//左子树放到0 
		CreateCode(HT,p->lchild);
		q=(HT->base+p->rchild);
		q=CopyNode(p,q);
    	q=InsertCode(HT->base+p->rchild,49);//右子树放到1 
    	CreateCode(HT,p->rchild);
	}
}

void OutputCode(HuffmanTree HT)
{
	HTNode *p;
	p=HT.base;
	FILE *output;
	output=fopen("Huffman.txt","w");
	if(output==NULL)
	{
		printf("Can't open the file Huffman.txt\n");
		exit(0);
	}
	int i=0,j;
	while(i<HT.LeafLength)
	{
		j=0;
		fprintf(output,"(%c) (%d) ",p->str,p->frequency);
		fprintf(output,"(");
		while(j<p->node.length)
		{
			if(*(p->node.base+j)==48)
			{
				fprintf(output,"0");
			}
			else fprintf(output,"1");
			j++;
		}
		fprintf(output,")\n");
		i++;
		p=(HT.base+i);
	}
}

HTNode *FindCode(HuffmanTree HT,char ch)
{
	HTNode *q;
	q=HT.base;
	int i=0;
	while(i<HT.LeafLength)
	{
		if(q->str==ch)
		{
			return q;
		}
		q++;
		i++;
	}
}

void Writecode(FILE *write,HTNode *p)
{
	int i=0;
	int *q;
	q=p->node.base;
	while(i<p->node.length)
	{
		fwrite(q,1,1,write);
		q++;
		i++;
	}
}

void WriteInCode(HuffmanTree HT)
{
	FILE *readsource;
	FILE *write;
	HTNode *p;
	readsource=fopen("source.txt","r");
	write=fopen("code.dat","wb");
	if(readsource==NULL)
	{
		printf("Can't open the file source.txt\n");
		exit(0);
	}
	if(write==NULL)
	{
		printf("Can't open the file code.dat\n");
		exit(0); 
	}
	char ch;
	ch=fgetc(readsource);
	while(!feof(readsource))
	{
		p=FindCode(HT,ch);
		Writecode(write,p);
		ch=fgetc(readsource);
	}
	fclose(readsource);
	fclose(write);
}

int ExsistCode(HTNode *q,int code[])
{
	int i=0;
	while(i<q->node.length)
	{
		if(code[i]!=*(q->node.base+i))
		{
			return 0;
		}
		i++;
	}
	return 1;
}

HTNode *JudgeCode(HuffmanTree HT,int code[])
{
	HTNode *q;
	q=HT.base;
	int i=0;
	while(i<HT.LeafLength)
	{
		if(ExsistCode(q,code))
		{
			return q;
		}
		i++;
		q++;
	}
	return NULL;
}

void ClearCode(int code[])
{
	int i=0;
	while(code[i]!=0)
	{
		code[i]=0;
		i++;
	}
}

void AddCode(FILE *read,int code[])
{
	int i=0;
	while(code[i]!=0)
	{
		i++;
	}
	fread(&code[i],1,1,read);
}

void ReCode(HuffmanTree HT)
{
	FILE *recode;
	FILE *read;
	HTNode *p;
	p=HT.base;
	int code[2000]={0};
	read=fopen("code.dat","rb");
	recode=fopen("recode.txt","w");
	if(read==NULL)
	{
		printf("Can't open the file code.dat\n");
		exit(0);
	}
	if(recode==NULL)
	{
		printf("Can't open the file recode.txt\n");
		exit(0); 
	}
	while(!feof(read))
	{
		p=JudgeCode(HT,code);
		if(p!=NULL)
		{
			fprintf(recode,"%c",p->str);
			ClearCode(code);
		}
		else
		{
			AddCode(read,code);
		}
		p=HT.base;
	}
}

int main()
{
	HuffmanTree HT;
	FILE *Input;
	Input=fopen("source.txt","r");
	if(Input==NULL)
	{
		printf("Can't open the file source.txt\n");
		exit(0);
	}
	CreateHuffmanTree(&HT,Input);
	CreateCode(&HT,HT.TotalLength-1);
	OutputCode(HT);
	fclose(Input);
	WriteInCode(HT);
	ReCode(HT);
	return 0;
}

