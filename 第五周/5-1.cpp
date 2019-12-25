//ABC##DE#G##F###
//���� ABCDEGF 
//���� CBEGDFA
//���� CGEFDBA
//��� ABCDEFG 

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct sqstack{
	BiTNode* *base;
	BiTNode* *top;
	int stacksize;
}SqStack;

typedef struct  QNode
{
	BiTNode* data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct Link
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue *Q)
{
	Q->front=(QueuePtr)malloc(sizeof(QNode));
	Q->rear=Q->front;
	Q->front->next=NULL;
}

void DeQueue(LinkQueue *Q,BiTNode **e)
{
	if(Q->front==Q->rear)
	{
		printf("�ö���Ϊ��");
		return ;
	}
	QNode *p,*q;
	p=Q->front->next;
	*e=p->data;
	q=p->next;
	Q->front->next=q;
	if(Q->rear==p) Q->rear=Q->front;
}

void EnQueue(LinkQueue *Q,BiTNode* e)
{
	QNode *p;
	p=(QNode*)malloc(sizeof(QNode));
	Q->rear->next=p;
	p->data=e;
	Q->rear=p;
	p->next=NULL;
}

int QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear){
		return 1;
	}
	else return 0;
}
void GetRear(LinkQueue *Q,BiTNode **e)
{
	if(Q->front==Q->rear)
	{
		printf("�ö���Ϊ��");
		return; 
	}
	QNode *p;
	p=Q->rear;
	*e=p->data;
}

void GetHead(LinkQueue *Q,BiTNode **e)
{
	if(Q->front==Q->rear)
	{
		printf("�ö���Ϊ��");
		return; 
	}
	QNode *p;
	p=Q->front->next;
	*e=p->data;
}

void InitStack(SqStack *stack)
{
	stack->base=(BiTNode**)malloc(STACK_INIT_SIZE*sizeof(BiTNode*));
	if(!stack->base) 
	{
		printf("����ջʧ�ܣ�"); 
	    exit(0);
	}
	stack->top=stack->base;
	stack->stacksize=STACK_INIT_SIZE;
}

void GetTop(SqStack *stack,BiTNode* *e)
{
	if(stack->top-stack->base==0){
		printf("��ջΪ��!");
	}
	*e=*(stack->top-1);
}

void Pop(SqStack *stack,BiTNode* *e)
{
	if(stack->top-stack->base==0)
	{
		printf("��ջΪ�գ�");
		return ;
	}
	*(e)=*(stack->top-1);
	stack->top--;
}

void Push(SqStack *stack,BiTNode* e)
{
	if(stack->top-stack->base==STACK_INIT_SIZE)
	{
		stack->base=(BiTNode* *)realloc(stack->base,(stack->stacksize+STACKINCREMENT)*sizeof(BiTNode*));
		stack->top=stack->base+stack->stacksize;
		stack->stacksize+=STACKINCREMENT;
	}
	if(!stack->base){
		printf("����Ԫ��ʱջ�������·���ռ����");
		return;
	}
    *(stack->top)=e;
    stack->top++;
}

int StackEmpty(SqStack stack)
{
	if(stack.top-stack.base!=0)
	{
		return 0; 
	}
	else return 1;
}

BiTree InitBiTree()
{
	BiTree T;
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;
	T->rchild=NULL;
	return T;
}

void DestroyTree(BiTree *T)
{
	if(*T!=NULL)
	{
		DestroyTree(&(*T)->lchild);
		DestroyTree(&(*T)->rchild);
		free(*T);
	}
	else return;
}

void CreateBiTree(BiTree *T)//���Ⱥ��������������н���ֵ��"#"��ʾ�� 
{
	char ch;
	ch=getchar();
	if(ch=='#') *T=NULL;
	else{
		*T=(BiTNode*)malloc(sizeof(BiTNode));
		if(!*T) exit(0);
		(*T)->data=ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
	return;
}//����

void ClearBiTree(BiTree *T)
{
	*T=NULL;
	printf("��ճɹ���\n");
}

int BiTreeEmpty(BiTree T)
{
	if(T==NULL){
		printf("����Ϊ�գ�\n");
		return 1; 
	} 
	else {
	    return 0;
	}
}

int BiTreeDepth(BiTree T)
{
	if(T==NULL) return 0;
	else if(BiTreeDepth(T->lchild)>=BiTreeDepth(T->rchild)){
		return BiTreeDepth(T->lchild)+1;
	}
	else return BiTreeDepth(T->rchild)+1;
}

char Root(BiTree T)
{
	if(T!=NULL) return T->data;
	else{
		printf("����Ϊ�գ�\n");
		return 0;
	} 
}

char Value(BiTree T,char e)
{
	int flag=0;
	BiTNode *p=T;
	SqStack stack;
	if(T->data==e) return T->data;
	InitStack(&stack);
	Push(&stack,T);
	while(StackEmpty(stack)!=1)
	{
		GetTop(&stack,&p);
		if(p&&p->data==e){
			flag=1;
			return p->data;
		}
		else{
			if(p!=NULL){
			    Pop(&stack,&p);
			    Push(&stack,p->rchild);
			    Push(&stack,p->lchild);	
			}
			else Pop(&stack,&p);
		}
	}
	if(!flag) return 0;
}

int Assign(BiTree *T,char *e,char value)
{
	int flag=0;
	BiTNode *p=*T;
	SqStack stack;
	InitStack(&stack);
	Push(&stack,*T);
	while(StackEmpty(stack)!=1)
	{
		GetTop(&stack,&p);
		if(p&&p->data==*e){
			flag=1;
			p->data=value;
			return 1;
		}
		else{
			if(p!=NULL){
			    Pop(&stack,&p);
			    Push(&stack,p->rchild);
			    Push(&stack,p->lchild);	
			}
			else Pop(&stack,&p);
		}
	}
	if(!flag) return 0;
}

BiTNode* Parent(BiTree T,char cur_e)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p,*q;
	p=T;
	if(T->data==cur_e) return NULL;
	EnQueue(&Q,p);
	while(p&&p->data!=cur_e)
	{
		q=p;
	    DeQueue(&Q,&p);
		if(q!=NULL){	
		    EnQueue(&Q,q->lchild);
		    GetRear(&Q,&p);
		    if(p&&p->data==cur_e) break;
			EnQueue(&Q,q->rchild);
			GetRear(&Q,&p);
			if(p&&p->data==cur_e) break;
			if(p==NULL) DeQueue(&Q,&p);
		}
		else DeQueue(&Q,&p);
	}
	return q;
}

BiTNode* LeftChild(BiTree T,char e)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p,*q;
	p=T;
	EnQueue(&Q,p);
	while(p&&p->data!=e)
	{
		q=p;
	    DeQueue(&Q,&p);
		if(p!=NULL){
			EnQueue(&Q,p->lchild);
			EnQueue(&Q,p->rchild);
		}
		else DeQueue(&Q,&p);
	}
	if(p) return p->lchild;
	else return NULL;
}

BiTNode* RightChild(BiTree T,char e)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p,*q;
	p=T;
	EnQueue(&Q,p);
	while(p&&p->data!=e)
	{
		q=p;
	    DeQueue(&Q,&p);
		if(p!=NULL){
			EnQueue(&Q,p->lchild);
			EnQueue(&Q,p->rchild);
		}
		else DeQueue(&Q,&p);
	}
	if(p) return p->rchild;
	else return NULL;
}

BiTNode* LeftSibling(BiTree T,char e)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p,*q;
	if(T->data==e) return NULL;
	p=T;
	EnQueue(&Q,p);
	EnQueue(&Q,NULL);
	while(!QueueEmpty(Q))
	{
		q=p;
		DeQueue(&Q,&p);
		if(p!=NULL){
			EnQueue(&Q,p->lchild);
			EnQueue(&Q,p->rchild);
			EnQueue(&Q,NULL);
			if(p->data==e){
				return q;
			}
		}
	}
	return NULL;//�����꣬û����� 
}

BiTNode* RightSibling(BiTree T,char e)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p,*q;
	if(T->data==e) return NULL;
	p=T;
	EnQueue(&Q,p);
	EnQueue(&Q,NULL);
	while(!QueueEmpty(Q))
	{
	    q=p;
	    DeQueue(&Q,&p);
		if(p!=NULL){
			EnQueue(&Q,p->rchild);
			EnQueue(&Q,p->lchild);
			EnQueue(&Q,NULL);
			if(p->data==e){
				return q;
			}
	    }
	}
	return NULL;
}

void InsertChild(BiTree* T,char p,int LR,BiTree* c)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *s,*q;
	s=*T;
	EnQueue(&Q,s);
	while(s->data!=p)
	{
		GetHead(&Q,&s);
		if(s!=NULL){
			EnQueue(&Q,s->lchild);
			EnQueue(&Q,s->rchild);
			DeQueue(&Q,&s);
		}
		else
		{
		    DeQueue(&Q,&s);
		    GetHead(&Q,&s);	
		}
	}
	if(s==NULL||s->data!=p){
		printf("�ý�㲻���ڣ�\n");
		return ;
	}
	if(!LR){
		q=s->lchild;
		s->lchild=*c;
		(*c)->rchild=q;
	}
	else{
		q=s->rchild;
		s->rchild=*c;
		(*c)->rchild=q;
	}
}

void Delete(BiTree *T,char p,int LR)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *s,*q;
	s=*T;
	EnQueue(&Q,s);
	while(s&&s->data!=p)
	{
		GetHead(&Q,&s);
		if(s!=NULL){
			EnQueue(&Q,s->lchild);
			EnQueue(&Q,s->rchild);
			DeQueue(&Q,&s);
		}
		else
		{
		    DeQueue(&Q,&s);
		    GetHead(&Q,&s);	
		}
	}
	if(s==NULL||s->data!=p)
	{
		printf("�ý�㲻���ڣ�\n");
		return ;
	}
	if(!LR){
		DestroyTree(&s->lchild);
		s->lchild=NULL;
	}
	else {
		DestroyTree(&s->rchild);
		s->rchild=NULL;
	}
}

void Visit(char e)
{
	printf("%c",e);
}
void PreOrderTraverse(BiTree T)
{
	if(T==NULL){
		return ;
	} 
	else{
		Visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	if(T==NULL){
		return ;
	} 
	else{
		InOrderTraverse(T->lchild);
		Visit(T->data);
		InOrderTraverse(T->rchild);
	}
} 

void PostOrderTraverse(BiTree T)
{
	if(T==NULL){
		return ;
	} 
	else{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		Visit(T->data);
	}
}

void LevelOrderTraverse(BiTree T)
{
	LinkQueue Q;
	InitQueue(&Q);
	BiTNode *p;
	p=T;
	EnQueue(&Q,p);
	while(!QueueEmpty(Q))
	{
		DeQueue(&Q,&p);
		if(p!=NULL){ 
			EnQueue(&Q,p->lchild);
			EnQueue(&Q,p->rchild);
			Visit(p->data);
		}
	}
}

int main()
{
	BiTree T,ano_T;
	BiTNode *p;
	int depth,LR,m,n;
	char c,value;
	while(m!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("ѧ��:031720106\n����:����˳");
	printf("��������Ҫ���еĲ�����\n");
	printf("��������Ҫ���еĲ�����\n");
	printf("1.InitBiTree\n");
	printf("2.DestroyBiTree\n");
	printf("3.CreateBiTree\n");
	printf("4.ClearBiTree\n");
	printf("5.BiTreeEmpty\n");
	printf("6.BiTreeDepth\n");
	printf("7.Root\n");
	printf("8.Value\n");
	printf("9.Assign\n");
	printf("10.Parent\n");
	printf("11.LeftChild\n");
	printf("12.RightChild\n");
	printf("13.LeftSibling\n"); 
	printf("14.RightSibling\n");
	printf("15.InsertChild\n");
	printf("16.DeleteChild\n");
	printf("17.PreOrderTraverse\n");
	printf("18.InOrderTraverse\n");
	printf("19.PostOrderTraverse\n");
	printf("20.LevelOrderTraverse\n");
	printf("0.exit\n");
	scanf("%d",&m);
	switch(m)
	{
		case 1:{
			system("cls");
			T=InitBiTree();
			printf("�ѳɹ�������\n");
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			DestroyTree(&T);
			printf("�ѳɹ���������\n");
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			getchar();
			CreateBiTree(&T); 
			printf("�ɹ�������\n");
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			ClearBiTree(&T); 
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			n=BiTreeEmpty(T);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			if(!BiTreeEmpty(T))
			{
				depth=BiTreeDepth(T);
			    printf("�������Ϊ%d\n",depth);
			}
			system("pause");
			break;
		}
		case 7:{ 
			system("cls");
			if(!BiTreeEmpty(T)){
				c=Root(T);
			    if(c!='0') printf("���ĸ�Ϊ%c\n",c);
			}
			system("pause");
			break;
		}
		case 8:{ 
			system("cls");
			printf("�����������ҵ��Ľ��\n");
			getchar();
			scanf("%c",&c);
			if(!BiTreeEmpty(T))
			{
				c=Value(T,c);
				if(c==0) printf("�ýڵ㲻���ڣ�\n");
				else printf("�ý��Ϊ%c\n",c);
			}
			
			system("pause");
			break;
		}
		case 9:{ 
			system("cls");
			getchar();
			printf("����������ı�Ľ��\n");
			scanf("%c",&c);
			getchar();
			printf("����������ı���Ϊʲôֵ��");
			scanf("%c",&value);
			if(!BiTreeEmpty(T))
			{
				n=Assign(&T,&c,value);
				if(n==1) printf("�ı�ɹ���\n");
				else printf("�ý�㲻���ڣ�\n");
			}
			
			system("pause");
			break;
		}
		case 10:{ 
			system("cls");
			getchar();
			printf("�����������ҵ��丸ĸ�Ľ�㣡\n");
			scanf("%c",&c);
			if(!BiTreeEmpty(T))
			{
				p=Parent(T,c);
			    if(p!=NULL)
			        printf("c���ĸ�ĸΪ%c\n",p->data);
			    else printf("�ý���޸�ĸ\n");
			} 
		    
			system("pause");
			break;
		}
		case 11:{ 
			system("cls");
			getchar();
			printf("�����������ҵ��Ľ������ӣ�\n");
			scanf("%c",&c);
			if(!BiTreeEmpty(T))
			{
				p=LeftChild(T,c);
				if(p!=NULL) printf("c����������%c\n",p->data);
				else printf("�ý��������\n");
			}
			
			system("pause");
			break;
		}
		case 12:{ 
			system("cls");
			getchar();
			printf("�����������ҵ��Ľ����Һ��ӣ�\n");
			scanf("%c",&c);
			if(!BiTreeEmpty(T))
			{
				p=RightChild(T,c);
				if(p!=NULL) printf("c�����Һ�����%c\n",p->data);
				else printf("�ý�����Һ���\n");
			}
			
			system("pause");
			break;
		}
		case 13:{
			system("cls");
			getchar();
			printf("�����������ҵ��Ľ������ֵܣ�\n");
			scanf("%c",&c);
			if(!BiTreeEmpty(T))
			{
				p=LeftSibling(T,c);
				if(p!=NULL) printf("c�������ֵ���%c\n",p->data);
				else printf("�ý�������ֵ�\n");
			}
		
			system("pause");
			break;
		}
		case 14:{
			system("cls");
			getchar();
			printf("�����������ҵ��Ľ������ֵܣ�\n");
			scanf("%c",&c);
			if(!BiTreeEmpty(T))
			{
				p=RightSibling(T,c);
				if(p!=NULL) printf("c�������ֵ���%c\n",p->data);
				else printf("�ý�������ֵ�\n");
			}
			
			system("pause");
			break;
		}
		case 15:{
			system("cls");
			getchar();
			printf("�����������ҵ��Ĳ���Ľ��\n");
			scanf("%c",&c);
			printf("������������뵽������������������\n");
			scanf("%d",&LR);
			ano_T=InitBiTree();
			printf("�뿪ʼ������ano_T\n");
			getchar();
			CreateBiTree(&ano_T);
			if(!BiTreeEmpty(T))
			InsertChild(&T,c,LR,&ano_T);
			system("pause");
			break;
		}
		case 16:{
			system("cls");
			getchar();
			printf("�����������ҵ��Ľ��\n");
			scanf("%c",&c);
			printf("����������ɾ��������������������\n");
			scanf("%d",&LR);
			if(!BiTreeEmpty(T))
			Delete(&T,c,LR);
			system("pause");
			break;
		}
		case 17:{
			system("cls");
			printf("�������\n");
			if(!BiTreeEmpty(T))
		    PreOrderTraverse(T);
			system("pause");
			break;
		}
		case 18:{
			system("cls");
			printf("�������\n");
			if(!BiTreeEmpty(T))
		    InOrderTraverse(T);
			system("pause");
			break;
		}
		case 19:{
			system("cls");
			printf("�������\n");
			if(!BiTreeEmpty(T))
		    PostOrderTraverse(T);
			system("pause");
			break;
		}
		case 20:{
			system("cls");
			printf("��α���\n");
			if(!BiTreeEmpty(T))
		    LevelOrderTraverse(T);
			system("pause");
			break;
		}
		case 0:{
			printf("�ѳɹ��˳���\n");
			exit(0);
			break;
		}
	}
	}
	return 0;
}
