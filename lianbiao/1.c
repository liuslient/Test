#include<stdio.h>
#include<stdlib.h>

typedef struct book
{
	int cost;
	struct book *next;
} Linklist;

//创建链表
Linklist *creat()
{
	int n,i;
	Linklist *head, *node, *end;
	head=(Linklist*)malloc(sizeof(Linklist));
	end=head;
	printf("请输入链表数据个数:\n");
	scanf("%d",&n);
	printf("请输入你的数据:\n");
	for(i=0;i<n;i++)
	{
		node=(Linklist*)malloc(sizeof(Linklist));
		scanf("%d",&node->cost);
		end->next=node;
		end=node;
	}
	end->next=NULL;
	return head;
}
//修改链表
void change(Linklist *list,int n)
{
	Linklist *h=list;
	int i=0;
	while(i<n&&h!=NULL)
	{
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		printf("请输入要修改的值:");
		scanf("%d",&h->cost);
	}
	else
	{
		printf("修改失败\n");
	}
}
//插入链表
void charu(Linklist *list,int n)
{
	Linklist *h=list,*p;
	int i=1;
	while(i<n&&h!=NULL)
	{
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		p=(Linklist*)malloc(sizeof(Linklist));
		printf("输入要插入的值:");
		scanf("%d",&p->cost);
		p->next=h->next;
		h->next=p;
	}
	else
	{
		printf("找不到节点\n");
	}
}
//查找链表
void find(Linklist *list,int n)
{
	Linklist *h=list;
	int i=0;
	while(i<n&&h!=NULL)
	{
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		printf("所查点的值:%d",h->cost);
	}
	else
	{
		printf("查找不到结果\n");
	}
}
//删除链表
void delete(Linklist *list,int n)
{
	Linklist *h=list,*p;
	int i=0;
	while(i<n&&h!=NULL)
	{
		p=h;
		h=h->next;
		i++;
	}
	if(h!=NULL)
	{
		p->next=h->next;
		free(h);
	}
	else
	{
		printf("无法删除\n");
	}
}
//输出链表
void output(Linklist *p)
{
	while(p->next!=NULL)
	{
		p=p->next;
		printf("%d ",p->cost);
	}
}

//链表逆置
void nizhi(Linklist *ph)
{
	Linklist *p=ph->next,*q;
	ph->next=NULL;
	while(p)
	{
		q=p->next;
		p->next=ph->next;
		ph->next=p;
		p=q;
	}
}
//主函数
int main()
{
	int n;
	Linklist *p;
	p=creat();
	printf("原数据:\n");
	output(p);
	printf("\n");
	printf("请输入想删除的位置:");
	scanf("%d",&n);
	delete(p,n);
	printf("删除后数据:\n");
	output(p);
	printf("\n");
	printf("请输入想插入的位置:");
	scanf("%d",&n);
	charu(p,n);
	printf("插入后数据:\n");
	output(p);
	printf("\n");
	printf("请输入要修改的位置:");
	scanf("%d",&n);
	change(p,n);
	printf("修改后数据:\n");
	output(p);
	printf("\n");
	printf("请输入要查点的位置:");
	scanf("%d",&n);
	find(p,n);
	printf("\n");
	nizhi(p);
	printf("逆置后数据:\n");
	output(p);
}
