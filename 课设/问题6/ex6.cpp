#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>

typedef struct node
{
	int num;
	struct node *next;
}Node,*NodeList;

typedef struct key
{
	int keynum;
	Node *next;
}Key;

void CreateSample(char filename[10][20])
{
	 int i,j;
	 FILE *In[10];
	 int a[20000];
	 for(j=0;j<10;j++)
	 {
	 	In[j]=fopen(filename[j],"w");
	 	if(In[j]==NULL)
	 	{
	 		printf("Can't open the file \n");
	 		exit(0);
	 	}
	 }
	 srand((unsigned)time(NULL));
	 for(j=0;j<10;j+=2)
	 {
	 	 for(i=0;i<20000;i++)
		 {
		 	a[i]=rand()%20000+1; 
		 	if((i+1)%20==0) 
		 	fprintf(In[j],"\n");
		 	fprintf(In[j],"%d ",a[i]);
		 }
		 for(i=20000-1;i>=0;i--)
		 {
		 	if((20000-i)%20==0) 
		 	fprintf(In[j+1],"\n");
		 	fprintf(In[j+1],"%d ",a[i]);
		 }
	 }
	 for(j=0;j<10;j++)
	 {
	 	fclose(In[j]);
	 }
}

void CreateArray(int Randnum[],FILE *out)
{
	int i,n;
	for(i=0;i<20000;i++)
	{
		fscanf(out,"%d",&Randnum[i]);
	}
}

void InsertSort(int Randnum[]) 
{
	int i,j;
	int flag;
	for(i=0;i<20000;i++)
	{
		flag=Randnum[20000-1];
		for(j=19999;j>i;j--)
		{
            Randnum[j]=Randnum[j-1];
		}
		for(;j>0;j--)
		{
			Randnum[j]=Randnum[j-1];
			if(flag>Randnum[j])
			{
				break;
			}
		}
		Randnum[j]=flag; 
	}
}//≤Â»Î≈≈–Ú 

void ShellInsert(int Randnum[],int dk)
{
	int i=dk,j;
	int flag;
	for(;i<20000;i++)
	{
		if(Randnum[i]<Randnum[i-dk])
		{
			flag=Randnum[i];
			Randnum[i]=Randnum[i-dk];
			for(j=i-dk;j>dk;j-=dk)
			{
				Randnum[j]=Randnum[j-dk];
				if(Randnum[j]<flag)
				    break;
			}
			Randnum[j]=flag;
		}
	}
}
void ShellSort(int Randnum[])
{
	int dlta[3]={5,3,1};
	int k=0;
	for(;k<3;k++)
	{
		ShellInsert(Randnum,dlta[k]);
	}
}

void SwapSort(int Randnum[])
{
	int i,j;
	int n,t;
	n=20000;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(Randnum[j+1]<Randnum[j])
			{
				t=Randnum[j+1];
				Randnum[j+1]=Randnum[j];
				Randnum[j]=t;
			}
		}
	}
}//√∞≈›≈≈–Ú 

void SelectSort(int Randnum[])
{
	int i,j;
	int t;
	int min;
	int flag=0;
	int n=20000;
	for(i=0;i<n;i++)
	{
		flag=i;
		min=Randnum[i];
		for(j=i;j<n;j++)
		{
			if(min>Randnum[j])
			{
				min=Randnum[j];
				flag=j;
			}
		}
		if(flag!=i)
		{
			t=Randnum[i];
			Randnum[i]=Randnum[flag];
			Randnum[flag]=t;
		}
	}
}//—°‘Ò≈≈–Ú 

void Merge(int Randnum[],int a[],int i,int m,int n)
{
	int j,k;
	int s=0;
	for(j=m+1,k=i;i<=m&&j<=n;k++)
	{
		if(Randnum[i]<Randnum[j]){
			a[k]=Randnum[i];
			i++; 
		}
		else{
			a[k]=Randnum[j];
			j++;
	    }
	}
	if(i<=m)
	{
		while(i<=m)
		{
			a[k]=Randnum[i];
			k++;
			i++;
		}
	}
	if(j<=n)
	{
		while(j<=n)
		{
			a[k]=Randnum[j];
			k++;
			j++;
		}
	}
}

void Output(int a[])
{
	int i=0;
	for(i=0;i<20000;i++)
	{
		printf("%d ",a[i]);
		if((i+1)%20==0) printf("\n");
	}
} 

void MSort(int Randnum[],int a[],int k)
{
	int i=0,j;
	while(i<=20000-2*k)
	{
		Merge(Randnum,a,i,i+k-1,i+2*k-1);
		i+=2*k;
	}
	if(i<20000-k+1)
	{
		Merge(Randnum,a,i,i+k-1,20000-1);
	}
	else 
	{
		for(j=i;j<20000;j++)
		{
			a[j]=Randnum[j];
		}
	}
	for(i=0;i<20000;i++)
	{
		Randnum[i]=a[i];
	}
}

void MergeSort(int Randnum[])
{
	int a[20000];
	int m=1;
	while(m<20000)
	{
		MSort(Randnum,a,m);
		m*=2;
	}
}//πÈ≤¢≈≈–Ú 

int Partition(int Randnum[],int low,int high)
{
	int t,i,j,key;
	i=low;
	j=high;
	key=Randnum[low];
	while(i<j)
	{
		while(i<j&&Randnum[j]>=key) j--;
		Randnum[i]=Randnum[j];
		while(i<j&&Randnum[i]<=key) i++;
		Randnum[j]=Randnum[i];
	}
	Randnum[i]=key;
	return i;
} 

void QSort(int Randnum[],int low,int high)
{
	int key;
	if(low<high)
	{
		key=Partition(Randnum,low,high);
		QSort(Randnum,low,key-1);
		QSort(Randnum,key+1,high);
    }
}//øÏÀŸ≈≈–Ú 

void HeapAdjust(int Randnum[],int s,int m)
{
	int flag;
	flag=Randnum[s-1];
	int j;
	for(j=2*s;j-1<m;j*=2)
	{
		if(j<m&&Randnum[j-1]>Randnum[j]) j++;
		if(flag<=Randnum[j-1]) break;
		Randnum[s-1]=Randnum[j-1];
		s=j;
	}
	Randnum[s-1]=flag;
}

void HeapSort(int Randnum[])
{
	int i;
	int t;
	for(i=20000/2;i>0;i--)
	{
		HeapAdjust(Randnum,i,20000);
	}
	for(i=19999;i>0;i--)
	{
		t=Randnum[i];
		Randnum[i]=Randnum[0];
		Randnum[0]=t;
		HeapAdjust(Randnum,1,i-1);
	}
}//∂—≈≈–Ú 

NodeList InitNodelist(NodeList L)
{
	L=(NodeList)malloc(sizeof(Node));
	L->next=NULL;
	return L;
}

NodeList CreateNodelist(NodeList L,int Randnum[])
{
	int i=0;
	Node *p,*q;
	q=L;
	while(i<20000)
	{
		p=(Node*)malloc(sizeof(Node));
		p->num=Randnum[i];
		i++;
		q->next=p;
		q=p;
	}
	q->next=NULL;
	return L;
}

int High(int Randnum[])
{
	int i=0;
	int max=0;
	int flag,tag=0;
	while(i<20000)
	{
		flag=Randnum[i];
		while(flag!=0)
		{
			tag++;
			flag=flag/10;
		}
		if(tag>max)
		{
			max=tag;
		}
		tag=0;
		i++;
	}
	return max;
}

NodeList Distribute(NodeList L,Key f[],Key e[],int i)
{
	Node *p1,*p2,*q1,*q2;
	p1=L->next;
	p2=p1->next;
	int flag;
	while(p1)
	{
		if(i!=0)
		    flag=(int)((p1->num)/(pow(10,i)))%10;
		else flag=(p1->num)%10;
		q2=f[flag].next;
		if(q2==NULL)
		{
			p1->next=q2;
			f[flag].next=p1;
		}
		else 
		{
			while(q2)
			{
				q1=q2;
				q2=q1->next;
			}
			p1->next=q2;
			q1->next=p1;
		}
		e[flag].next=p1;
		p1=p2;
		if(p2!=NULL)
		{
			p2=p1->next;
		}
	}
	L->next=NULL;
	return L;
}

NodeList Collect(NodeList L,Key f[],Key e[])
{
	int i;
	Node *p1,*p2,*q;
	q=L; 
	for(i=0;i<10;i++)
	{
		p1=f[i].next;
		if(p1==NULL)
		    continue;
		q->next=p1;
		p2=p1->next;
		while(p2)
		{
			p1=p2;
			p2=p1->next;
		}
		q=p1;
		f[i].next=NULL;
		e[i].next=NULL;
	}
	q->next=NULL;
	return L;
}

double RadixSort(int Randnum[])
{
	time_t time_start;
	time_t time_over;
	Key e[10];
	Key f[10];
	NodeList L;
	int i=0,n;
	for(i=0;i<10;i++)
	{
		e[i].keynum=i;
		f[i].keynum=i;
		f[i].next=NULL;
		e[i].next=NULL;
	}
	L=InitNodelist(L);
	L=CreateNodelist(L,Randnum);
	n=High(Randnum);
	time_start=clock();
	for(i=0;i<n;i++)
	{
		L=Distribute(L,f,e,i);
		L=Collect(L,f,e);
	}
	time_over=clock();
	return (double)(time_over-time_start)/CLOCKS_PER_SEC;
}

void Output(int Randnum[],char filename[10][20])
{
	time_t time_start;
	time_t time_over;
	FILE *In[10];
	int i=0;
	for(i=0;i<10;i++)
	{
		printf("µ⁄%d∏ˆ—˘±æ£∫\n",i+1);
		In[i]=fopen(filename[i],"r");
		CreateArray(Randnum,In[i]);
	    double run_time;
	    run_time=RadixSort(Randnum); 
		printf("ª˘ ˝≈≈–Ú: %.5lf\n",run_time);
		CreateArray(Randnum,In[i]);
		time_start=clock();
	    QSort(Randnum,0,19999); 
		time_over=clock();
		printf("øÏÀŸ≈≈–Ú: %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC);
		CreateArray(Randnum,In[i]);
		time_start=clock();
		InsertSort(Randnum);
		time_over=clock();
		printf("≤Â»Î≈≈–Ú: %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC); 
		CreateArray(Randnum,In[i]);
		time_start=clock();
		ShellSort(Randnum);
		time_over=clock();
		printf("œ£∂˚≈≈–Ú: %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC); 
		CreateArray(Randnum,In[i]);
		time_start=clock();
		SwapSort(Randnum);
		time_over=clock();
		printf("Ωªªª≈≈–Ú: %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC);
		CreateArray(Randnum,In[i]);
		time_start=clock();
		SelectSort(Randnum);
		time_over=clock();
		printf("—°‘Ò≈≈–Ú: %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC);
		CreateArray(Randnum,In[i]);
		time_start=clock();
		HeapSort(Randnum);
		time_over=clock();
		printf("∂—≈≈–Ú:  %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC);
		CreateArray(Randnum,In[i]);
		time_start=clock();
		MergeSort(Randnum);
		time_over=clock();
		printf("πÈ≤¢≈≈–Ú: %.5lf\n",(double)(time_over-time_start)/CLOCKS_PER_SEC);
		printf("\n\n");
	}
}

int main()
{
	int Randnum[20000];
	char filename[10][20]={"Sample1.txt","Sample2.txt","Sample3.txt","Sample4.txt","Sample5.txt","Sample6.txt","Sample7.txt","Sample8.txt","Sample9.txt","Sample10.txt"};
	CreateSample(filename);
    Output(Randnum,filename); 
    return 0;
}
