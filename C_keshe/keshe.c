#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//声明函数区域 
void output();                                 //浏览电影信息
void input();                                  //录入信息
void menu();                                   //功能目录 
void selects();                                //选择功能函数 
void change();                                 //电影信息修改
void search();                                 //电影信息查询
void insert();                                 //插入电影信息 
void delete();                                 //删除电影信息
void statist();                                //统计电影信息 
void sort();                                   //电影信息排序 

//电影信息 
typedef struct movie
{
	char number[20];                //电影编号 
	char name[10];                  //电影名称 
	int price;                      //票价 
	int people;                     //观看人次 
	char publish[10];               //出版公司  
	struct movie *next;             //指针域 
} Linklist; 

//头节点
Linklist* head = NULL;

//录入信息 
void input()
{
	Linklist *p1 = (Linklist*)malloc(sizeof(Linklist));     //定义一个要录入的数据
	p1->next=NULL;
	if(head==NULL)                                          //头插法 
	{
		head=p1;
	}
	else
	{
		p1->next=head;
		head=p1;
	}
	printf("请输入电影编号\n");
	scanf("%s",p1->number);
	
	printf("请输入电影名称\n");
	scanf("%s",p1->name); 
	
	printf("请输入电影票价\n");
	scanf("%d",&p1->price); 
	
	printf("请输入电影观看人次\n");
	scanf("%d",&p1->people); 
	
	printf("请输入电影出版公司\n");
	scanf("%s",p1->publish);
	
	printf("---【录入电影信息完成】---\n");
	
	system("pause");
	system("cls");
}

//功能目录 
void menu()
{
	printf("*********************************************************\n");
	printf("*\t\t欢迎使用影院管理系统\t\t\t*\n");
	printf("*********************************************************\n");
	printf("*\t\t  请选择下列功能    \t\t\t*\n");
	printf("*********************************************************\n");
	printf("*\t\t  1.录入电影信息    \t\t\t*\n");
	printf("*\t\t  2.修改电影信息    \t\t\t*\n");
	printf("*\t\t  3.删除电影信息    \t\t\t*\n");
	printf("*\t\t  4.查询电影信息    \t\t\t*\n");
	printf("*\t\t  5.电影信息排序    \t\t\t*\n");
	printf("*\t\t  6.统计电影信息    \t\t\t*\n");
	printf("*\t\t  7.插入电影信息    \t\t\t*\n");
	printf("*\t\t  8.浏览电影信息    \t\t\t*\n");
	printf("*\t\t  0.退出系统        \t\t\t*\n");
	printf("*********************************************************\n");
	printf("请选择你要的功能:"); 
}

//选择功能函数 
void selects()
{
	int shuru;
	scanf("%d",&shuru);
	switch(shuru)
	{
		case 1:
			printf("---【录入电影信息】---\n");
			input();
			break;	
		case 2:
			printf("---【修改电影信息】---\n");
			change();
			break;
		case 3:
			printf("---【删除电影信息】---\n");
			delete();
			break;
		case 4:
			printf("---【查询电影信息】---\n");
			search();
			break;
		case 5:
			printf("---【电影信息排序】---\n");
			sort(); 
			break;
		case 6:
			printf("---【统计电影信息】---\n");
			statist();
			break;
		case 7:
			printf("---【插入电影信息】---\n");
			insert();
			break;
		case 8:
			printf("---【浏览电影信息】---\n");
			output();
			break;
		case 0:
			printf("---【已经安全退出系统】---\n");
			break;
		default:
			printf("---【输入异常！！！请重新输入】---\n");
			break; 
	}
}

//电影信息修改
void change()
{
	int n,j;
	char i;
	Linklist* p=head;
	printf("1.编号\t2.票价\n");
	printf("请输入你要修改的项目:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			printf("请输入要修改的编号:");
			scanf("%s",&i);
			while(p!=NULL)
			{
				if(strcmp(p->number,&i)==0)
				{
					printf("输入想修改为的编号:");
					scanf("%s",&p->number);
					printf("---【修改完成】---\n");
				}
				else
				{
					printf("---【修改失败】---\n");
				}
				p=p->next;
			}
			break;
			
		case 2:
			printf("请输入要修改的票价:");
			scanf("%d",&j);
			while(p!=NULL)
			{
				if(p->price==j)
				{
					printf("输入想修改为的编号:");
					scanf("%d",&p->price);
					printf("---【修改完成】---\n");
				}
				else
				{
					printf("---【修改失败】---\n");
				}
				p=p->next;
			}
			break;
	}
}

//电影信息查询
void search()
{
	int n,j;
	char i;
	Linklist* p=head;
	printf("1.编号\t2.名称\t3.票价\t4.观看人次\t5.出版公司\t6.编号和票价\n\n");
	printf("请输入你要查询的项目:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			printf("请输入编号:");
			scanf("%s",&i);
			while(p!=NULL)
			{
				
				if(strcmp(p->number,&i)==0)                                //简单的查找，但要加取地址符 
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
				}
				else
				{
					printf("---【没有找到】---\n");
				}
				p=p->next;
			}
			break;
			
		case 2:
			printf("请输入名称:");
			scanf("%s",&i);
			while(p!=NULL)
			{
				
				if(strcmp(p->name,&i)==0)
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
				}
				else
				{
					printf("---【没有找到】---\n");
				}
				p=p->next;
			}
			break;
			
		case 3:
			printf("请输入票价:");
			scanf("%d",&j);
			while(p!=NULL)
			{
				
				if(p->price==j)
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
				}
				else
				{
					printf("---【没有找到】---\n");
				}
				p=p->next;
			}
			break;
			
		case 4:
			printf("请输入人次:");
			scanf("%d",&j);
			while(p!=NULL)
			{
				
				if(p->people==j)
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
				}
				else
				{
					printf("---【没有找到】---\n");
				}
				p=p->next;
			}
			break;
			
		case 5:
			printf("请输入出版公司:");
			scanf("%s",&i);
			while(p!=NULL)
			{
				
				if(strcmp(p->publish,&i)==0)       //要加地址才能比较 
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
				}
				else
				{
					printf("---【没有找到】---\n");
				}
				p=p->next;
			}
			break;
		case 6:
			printf("请输入编号:");
			scanf("%s",&i);
			printf("请输入票价:");
			scanf("%d",&j);
			while(p!=NULL)
			{
				
				if((strcmp(p->number,&i)==0)||(p->price==j))            //要加取地址符才能比较，不加取地址符字符串查找不成功 
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
				}
				else
				{
					printf("---【没有找到】---\n");
				}
				p=p->next;
			}
			break;
	}
}

//插入电影信息
void insert()
{
	int n;
	char i;
	Linklist* p=head,*p1;
	printf("请输入 1 进行插入操作:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			printf("请输入编号(会插入在其后):");
			scanf("%s",&i);
			while(p!=NULL)
			{
				
				if(strcmp(p->number,&i)==0)
				{
					p1=(Linklist*)malloc(sizeof(Linklist));               //开辟空间 
	            	printf("请输入电影编号\n");
                    scanf("%s",p1->number);
	
                    printf("请输入电影名称\n");
                    scanf("%s",p1->name); 
	
                    printf("请输入电影票价\n");
                    scanf("%d",&p1->price); 
	
                    printf("请输入电影观看人次\n");
                    scanf("%d",&p1->people); 
	
                    printf("请输入电影出版公司\n");
                    scanf("%s",p1->publish);
	
                    printf("插入电影信息完成\n");
                    p1->next=p->next;
                    p->next=p1;
				}
				p=p->next;
			}
			break;
		default:
			printf("---【输入非法！请重新输入】---\n");
			break;
	}
}

//删除电影信息
void delete()
{
	int n;
	char i;
	Linklist* p,*p1=head;
	p=p1->next;                                       //看书上的操作，不知道为什么只剩一个无法删除 
	printf("请输入 1 进行删除操作:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			printf("请输入要删除的编号:");
			scanf("%s",&i);
			while(p!=NULL)
			{
				if(strcmp(p->number,&i)==0)
				{
					printf("\t\t【以下是你要删除的电影信息】\n\n");
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
					p1->next=p->next; 
					free(p); 
					printf("---【已经安全删除】---\n");
				}
				p1=p;
				p=p->next;
			}
			break;
		default:
			printf("---【输入非法！请重新输入】---\n");
			break;
	}
}

//统计电影信息
void statist()
{
	int n,i,j,k,m,a=0,b=0;
	Linklist *p=head;
	printf("1.票价统计\t2.票价和人次统计\n");
	printf("请输入你想要的功能:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			printf("请输入要统计的票价(之上):");
			scanf("%d",&i);
			while(p!=NULL)                  //遍历链表进行查找 
			{
				j=p->price;
				if(j>i)
				{
					a++;
				}
				else
				{
					b++;
				}
				p=p->next;
			}
			printf("---【票价%d之上有%d部电影】---\n",i,a);
			printf("---【票价%d之下有%d部电影】---\n",i,b);
			break;
		case 2:
			printf("请输入要统计的票价(之上):");
			scanf("%d",&i);
			printf("请输入要统计的人次(之上):");
			scanf("%d",&j);
			while(p!=NULL)
			{
				k=p->price;
				m=p->people;
				if(k>i&&m>j)
				{
					a++;
				}
				else
				{
					b++;
				}
				p=p->next;
			}
			printf("---【票价%d之上且人次%d之上有%d部电影】---\n",i,j,a);
			printf("---【票价%d之下且人次%d之下有%d部电影】---\n",i,j,b);
			break;
		default:
			printf("---【输入异常！！！请重新输入】---\n");
			break;
	}
}

//电影信息排序
void sort()                    //采用了冒泡排序 
{
	int n,j;
	char i;
	Linklist* p=head,*p1;
	p1=NULL;
	printf("1.票价从低向高\t2.票价从高到低\n");
	printf("请选择排序方式:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			while(p!=p1)
			{
				while(p->next!=p1)
				{
					if(p->price>p->next->price)
					{
						j=p->price;                                      //交换 
						p->price=p->next->price;
						p->next->price=j;
					}
					p=p->next;                    //向下顺延 
				}
				p1=p;
				p=head;
			}
			printf("---【排序已经完成】---\n");
			break;
		case 2:
		    while(p!=p1)
			{
				while(p->next!=p1)
				{
					if(p->price<p->next->price)
					{
						j=p->price;
						p->price=p->next->price;
						p->next->price=j;
					}
					p=p->next;
				}
				p1=p;
				p=head;
			}
			printf("---【排序已经完成】---\n");
			break;
		default:
			printf("---【输入异常！！！请重新输入】---\n");
			break;
	}
}

//浏览电影信息
void output()
{
	system("cls");
	printf("*********************************************************\n");
	printf("*\t\t   影院影片列表     \t\t\t*\n");
	printf("*********************************************************\n");
	printf("*编号\t名称\t票价\t观看人次\t出版公司\t*\n");
	Linklist* p=head;
	while(p!=NULL)                                                            //遍历链表 
	{
		printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
		p=p->next;
	}
	printf("*********************************************************\n\n");
}

//主函数 
int main()
{
	int i=5;
	char c[]={"200108"};
	char s[20];
	while(i)
	{
		printf("请输入登录密码:");
		scanf("%s",s);
		if(!strcmp(s,c))                                //字符串的比较，在查询功能中起到了作用 
		{
			while(1)
        	{
	        	menu();                                 //显示目录
	        	selects();                              //选择功能函数 
	        	system("pause");                        //暂停 
	        	system("cls");                          //清屏，没有这个会重复出现目录界面 
	        }
		}
		else
		{
			i--;
			printf("【输入错误】\n【剩余输入次数为%d】\n",i);
		}
	}
	if(i==0)
	{
		printf("---【系统退出】---"); 
	}
	return 0; 
}
