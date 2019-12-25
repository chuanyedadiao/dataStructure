#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define LIST_INIT_SIZE 100
#define LISTINCERMENT 10

typedef struct goods
{
	char Goods_name[20];
	float Price;
	int Sales;
}Goods;

typedef struct GoodsNode
{
	Goods product;
	struct GoodsNode *next_goods;
}GoodsNode,*GoodsList;//构建单个商铺里面的商品链

typedef struct shop
{
	int ShopNum;
	char ShopName[20];
	int reputation;//(0-5)
	GoodsList goodslist;//每个商铺含有一个商品链 
	struct shop *next_shop;
}Shop,*ShopList;

typedef struct search
{
	struct search *front;
	struct search *next;
	int ShopNum;
	char ShopName[20];
	int reputation;
	Goods product;
}Search,*SearchList;

typedef struct salenode
{
	char GoodsName[20];
	int Sales;
}SaleNode;

typedef struct salelist
{
	SaleNode *base;
	int length;
	int listsize;
}SaleList;

ShopList InitShop(ShopList Shops)
{
	FILE *in;
	in=fopen("ShopsIn.txt","r");
	if(in==NULL)
	{
		printf("Can't open the file ShopsIn.txt\n");
		exit(0);
	}
	Shop* p1,*p2;
	Shops=(ShopList)malloc(sizeof(Shop));
	p2=Shops;
	GoodsNode* q1,*q2;
	char ch1,ch2;
	while(!feof(in))
	{
		p1=(Shop*)malloc(sizeof(Shop));
		fscanf(in,"%d",&p1->ShopNum);
		fscanf(in,"%s",p1->ShopName);
		fscanf(in,"%d",&p1->reputation);
		p1->goodslist=(GoodsList)malloc(sizeof(GoodsNode));
		q2=p1->goodslist;
		ch2=fgetc(in);
		ch1=fgetc(in);
		while(!feof(in)&&ch1=='(')
		{
			q1=(GoodsNode*)malloc(sizeof(GoodsNode));
			fscanf(in,"%s",q1->product.Goods_name);
			fscanf(in,"%f",&q1->product.Price);
			fscanf(in,"%d",&q1->product.Sales);
			q2->next_goods=q1;
			q2=q1;
			ch2=fgetc(in);
			ch1=fgetc(in);
		}
		q2->next_goods=NULL;
		p2->next_shop=p1;
		p2=p1;
	}//建立商店的单链表，以及商铺中的商品链表 
	p2->next_shop=NULL;
	fclose(in);
	return Shops;
}//输入 check 

ShopList InsertShop(ShopList Shops)
{
	FILE *insert;
	insert=fopen("ShopsInsert.txt","r");
	if(insert==NULL)
	{
		printf("Can't open the file ShopsInsert.txt\n");
		exit(0);
	}
	Shop* p1,*p2;
	GoodsNode* q1,*q2;
	char ch1,ch2;
	int number;
	p1=Shops;
	p2=p1->next_shop;
	while(p2)
	{
		p1=p2;
		p2=p1->next_shop;
	}
	number=p1->ShopNum;
	while(!feof(insert))
	{
		p2=(Shop*)malloc(sizeof(Shop));
		p2->ShopNum=number+1;
		fscanf(insert,"%s",p2->ShopName);
		fscanf(insert,"%d",&p2->reputation);
		ch2=fgetc(insert);
		ch1=fgetc(insert);
		p2->goodslist=(GoodsList)malloc(sizeof(GoodsNode));
		q2=p2->goodslist;
		while(!feof(insert)&&ch1=='(')
		{
			q1=(GoodsNode*)malloc(sizeof(GoodsNode));
			fscanf(insert,"%s",q1->product.Goods_name);
			fscanf(insert,"%f",&q1->product.Price);
			fscanf(insert,"%d",&q1->product.Sales);
			q2->next_goods=q1;
			q2=q1;
			ch2=fgetc(insert);
			ch1=fgetc(insert);
		}
		printf("\n");
		q2->next_goods=NULL; 
		number++;
		p1->next_shop=p2;
		p1=p2;
	}
	p1->next_shop=NULL;
	fclose(insert);
	return Shops;
}//插入商铺 

ShopList DeleteShop(ShopList Shops)
{
	int number;
	printf("请输入你想删除的商铺的编号\n");
	scanf("%d",&number);
	Shop* p1,*p2,*s;
	p1=Shops;
	p2=p1->next_shop;
	while(p2)
	{
		if(p2->ShopNum==number) break;
		p1=p2;
		p2=p1->next_shop;
	}
	if(p2==NULL){
		printf("该商铺不存在\n");
		return Shops;
	}
	else{
		s=p2;
		p2=p2->next_shop;
		p1->next_shop=p2;
		free(s);
		while(p2)
		{
			p2->ShopNum--;
			p1=p2;
			p2=p1->next_shop;
		}
	}
	return Shops;
}//删除商铺 

GoodsNode* ExistGoods(Shop* p2,char SearchGoods[])
{
	GoodsNode *q1,*q2;
	q1=p2->goodslist;
	q2=q1->next_goods;
	while(q2)
	{
		if(strcmp(q2->product.Goods_name,SearchGoods)==0)
		{
			return q2;
		}
		q1=q2;
		q2=q1->next_goods;
	}
	return NULL;
}//检查该商铺中有无该商品 

SearchList InsertSearchList(SearchList searchlist,Shop* p2,GoodsNode *q)
{
	Search *s1,*s2,*flag;
	s1=searchlist;
	s2=s1->next;
	while(s2!=searchlist)
	{
		if(p2->reputation>s2->reputation)
		{
			break;
		}
		else if(p2->reputation==s2->reputation)
		{
			if(q->product.Sales>s2->product.Sales){
				break;
			}
		}
		s1=s2;
		s2=s1->next;
	}
	flag=(Search*)malloc(sizeof(Search));
	flag->product=q->product;
	flag->reputation=p2->reputation;
	strcpy(flag->ShopName,p2->ShopName);
	flag->ShopNum=p2->ShopNum;
	s1->next=flag;
	flag->front=s1;
	flag->next=s2;
	s2->front=flag;
	return  searchlist;
}
void OutputSearchList(SearchList searchlist)
{
	Search *s1,*s2;
	s1=searchlist;
	s2=s1->next;
	while(s2!=searchlist)
	{
		printf("商铺编号:%d  商铺名:%s  商铺声誉:%d",s2->ShopNum,s2->ShopName,s2->reputation);
		printf("\t商品名:%s  商品价格:%.2f  商品销量:%d\n",s2->product.Goods_name,s2->product.Price,s2->product.Sales);
	    s1=s2;
	    s2=s1->next;
	}
}
void SearchGood(ShopList Shops)
{
	char SearchGoods[20];
	printf("请输入想找到的商品的名字\n");
	scanf("%s",SearchGoods);
	Shop* p1,*p2;
	GoodsNode* q;
	p1=Shops;
	p2=p1->next_shop;
	SearchList searchlist;
	searchlist=(SearchList)malloc(sizeof(Search));
	searchlist->next=searchlist;
	searchlist->front=searchlist;
	while(p2)
	{
		q=ExistGoods(p2,SearchGoods);
		if(q)
		{
			searchlist=InsertSearchList(searchlist,p2,q);
		}
		p1=p2;
		p2=p1->next_shop;
	}
	OutputSearchList(searchlist);
}//查询某一种商品名称，建立一个双向循环链表 check

void printSearchList(SearchList searchlist)
{
	Search *s1,*s2;
	int i=1;
	s1=searchlist;
	s2=s1->next;
	while(s2!=searchlist)
	{
		printf("%d: %d %s %d",i,s2->ShopNum,s2->ShopName,s2->reputation);
		printf("(%s %.2f %d)",s2->product.Goods_name,s2->product.Price,s2->product.Sales);
	    s1=s2;
	    s2=s1->next;
	    printf("\n");
	}
}//输出查找商品双向链表的信息 

ShopList BuyGoods(ShopList Shops)
{
	char BuyShopName[20];
	char BuyGoodsName[20];
	int count;
	printf("请问想在哪个商铺购买商品\n");
	scanf("%s",BuyShopName);
	printf("请问想购买什么商品以及购买的数量\n");
	scanf("%s%d",BuyGoodsName,&count);
	Shop *p1,*p2;
	GoodsNode *q1,*q2; 
	p1=Shops;
	p2=p1->next_shop;
	q1=p2->goodslist;
	q2=q1->next_goods;
	while(p2)
	{
		if(strcmp(p2->ShopName,BuyShopName)==0)
		{
			while(q2)
			{
				if(strcmp(q2->product.Goods_name,BuyGoodsName)==0)
				{
					q2->product.Sales+=count;
					printf("%s %d\n",q2->product.Goods_name,q2->product.Sales);	
					break;
				}
		        q1=q2;
				q2=q1->next_goods;
			}
			if(q2==NULL)
			{
				printf("该商铺中不存在该商品\n");
			}
			break;
		}
		p1=p2;
		p2=p1->next_shop;
		if(p2!=NULL)
		{
			q1=p2->goodslist;
			q2=q1->next_goods;		
		}
	}
	if(p2==NULL)
	{
		printf("不存在该商铺\n");
	}
	return Shops;
}
void InitSaleList(SaleList *sale)
{
	sale->base=(SaleNode *)malloc(LIST_INIT_SIZE*sizeof(SaleNode));
	if(!sale->base) 
	{
		printf("创建顺序表失败！"); 
	    exit(0);
	}
	sale->length=0;
	sale->listsize=LIST_INIT_SIZE;
}

void InsertSaleList(SaleList *sale,GoodsNode *flag)
{
	SaleNode *newbase;
	if(sale->length>=sale->listsize)
	{
		newbase=(SaleNode *)realloc(sale->base,(sale->listsize+LISTINCERMENT)*sizeof(SaleNode));
		sale->base=newbase;
		sale->listsize+=LISTINCERMENT;
	}
	if((sale->base+sale->length)->GoodsName);
	if(flag->product.Goods_name);
	strcpy(sale->base[sale->length].GoodsName,flag->product.Goods_name);
	(sale->base+sale->length)->Sales=flag->product.Sales;
	sale->length++;
}

void SaleChange(SaleList *sale,GoodsNode *flag)
{
	int i;
	for(i=0;i<sale->length;i++)
	{
		if(strcmp((sale->base+i)->GoodsName,flag->product.Goods_name)==0)
		{
			(sale->base+i)->Sales+=flag->product.Sales;
			break;
		}
	}
} 
GoodsNode* ExistInSaleList(SaleList sale,GoodsNode *flag)
{
	int i;
	for(i=0;i<sale.length;i++)
	{
		if(strcmp((sale.base+i)->GoodsName,flag->product.Goods_name)==0)
		{
			return flag;
		}
	}
	return NULL;
}

void OutputSaleList(SaleList sale)
{
	int i;
	for(i=0;i<sale.length;i++)
	{
		printf("%d:%s %d\n",i+1,(sale.base+i)->GoodsName,(sale.base+i)->Sales);
	}
}

void SaleSort(ShopList Shops)
{
	SaleList sale;
	InitSaleList(&sale);
	Shop *p1,*p2;
	p1=Shops;
	p2=p1->next_shop;
	GoodsNode *q1,*q2,*flag;
	q1=p2->goodslist;
	q2=q1->next_goods;
	while(p2)
	{
		while(q2)
		{
			flag=ExistInSaleList(sale,q2);
			if(flag)
			{
				SaleChange(&sale,q2);
			}
			else InsertSaleList(&sale,q2);
			q1=q2;
			q2=q1->next_goods;
		}
		p1=p2;
		p2=p1->next_shop; 
		if(p2!=NULL)
		{
			q1=p2->goodslist;
	        q2=q1->next_goods;
		}
	}
	OutputSaleList(sale);
}

void PrintShops(ShopList Shops)
{
	FILE *output;
	output=fopen("ShopsOut.txt","w");
	if(output==NULL)
	{
		printf("Can't open the file ShopsIn.txt\n");
		exit(0);
	}
	Shop *p1,*p2;
	GoodsNode *q1,*q2;
	p1=Shops;
	p2=p1->next_shop;
	q1=p2->goodslist;
	q2=q1->next_goods;
	fprintf(output,"商铺编号，商铺名，商铺信誉，括号内为商品和商品价格以及其销量\n");
	while(p2)
	{
		fprintf(output,"%d %s %d",p2->ShopNum,p2->ShopName,p2->reputation);
		while(q2)
		{
		    fprintf(output,"(%s %.2f %d) ",q2->product.Goods_name,q2->product.Price,q2->product.Sales);
		    q1=q2;
		    q2=q1->next_goods;
		}
		fprintf(output,"\n");
	    p1=p2;
	    p2=p1->next_shop;
	    if(p2!=NULL)
	    {
	    	q1=p2->goodslist;
	        q2=q1->next_goods;
	    }
	}
	fclose(output);
}

int main()
{
	ShopList Shops;
	int m=1;
	while(m!=0){
	system("cls");
	system("date/t");
	system("time/t");
	printf("学号:031720106\n姓名:徐宇顺");
	printf("请输入需要进行的操作：\n");
	printf("1.建造商铺链\n");
	printf("2.增加商铺\n");
	printf("3.删除商铺\n");
	printf("4.在所有商铺中查询某个商品\n");
	printf("5.购买商品\n");
	printf("6.输出所有的商品和销量\n");
	printf("0.exit\n");
	scanf("%d",&m);
	switch(m)
	{
		case 1:{
			system("cls");
			Shops=InitShop(Shops);
			PrintShops(Shops);
			system("pause");
			break;
		}
		case 2:{ 
			system("cls");
			Shops=InsertShop(Shops); 
			PrintShops(Shops);
			system("pause");
			break;
		}
		case 3:{ 
			system("cls");
			Shops=DeleteShop(Shops);
			PrintShops(Shops);
			system("pause");
			break;
		}
		case 4:{ 
			system("cls");
			SearchGood(Shops);
			system("pause");
			break;
		}
		case 5:{ 
			system("cls");
			Shops=BuyGoods(Shops);
			PrintShops(Shops);
			system("pause");
			break;
		}
		case 6:{ 
			system("cls");
			SaleSort(Shops);
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
