#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//声明函数区域 
void output();                                 //浏览电影信息
void menu();                                   //功能目录 
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
Linklist *input()                //尾插发建立链表 
{
	int n,i;
	Linklist *head, *node, *end;
	head=(Linklist*)malloc(sizeof(Linklist));                 //开辟空间 
	end=head;
	do
	{
		node=(Linklist*)malloc(sizeof(Linklist));
		printf("请输入电影编号\n");
	    scanf("%s",node->number);
	
    	printf("请输入电影名称\n");
    	scanf("%s",node->name); 
	
    	printf("请输入电影票价\n");
    	scanf("%d",&node->price); 
	
    	printf("请输入电影观看人次\n");
    	scanf("%d",&node->people); 
	
    	printf("请输入电影出版公司\n");
    	scanf("%s",node->publish);
	
    	printf("---【录入电影信息完成】---\n");
    	
		end->next=node;                  //尾插新节点 
		end=node;                        //指向尾结点 
		printf("\t1.是\t2.否\n");
		printf("请输入是否要录入数据");
		scanf("%d",&n);
	}
	while(n==1);
	end->next=NULL;
	return (head);
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

//电影信息修改
void change(Linklist *list)
{
	int n,j;
	char i;
	Linklist* p=list;
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
				p=p->next;
			}
			break;
	}
}

//电影信息查询
void search(Linklist *list)
{
	int n,j;
	char i;
	Linklist* p=list;
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
				p=p->next;
			}
			break;
			
		case 5:
			printf("请输入出版公司:");
			scanf("%s",&i);
			while(p!=NULL)
			{
				
				if(strcmp(p->publish,&i)==0)       
				{
					printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
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
				p=p->next;
			}
			break;
	}
}

//插入电影信息
void insert(Linklist *list)
{
	int n;
	char i;
	Linklist* p=list,*p1;
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
void delete(Linklist *list)
{
	int n;
	char i;
	Linklist* p,*p1=list;
	p=p1->next;
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
					free(p);                                           //释放空间 
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
void statist(Linklist *list)
{
	int n,i,j,k,m,a=0,b=0;
	Linklist *p=list;
	printf("1.票价统计\t2.票价和人次统计\n");
	printf("请输入你想要的功能:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			printf("请输入要统计的票价(之上):");
			scanf("%d",&i);
			while(p->next!=NULL)                  //遍历链表进行查找 
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
			while(p->next!=NULL)                  //遍历链表进行查找     
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
void sort(Linklist *list)                    //采用了冒泡排序 
{
	int n,j,h;
	char i,*a,*b,*c;
	Linklist* p,*q,*p1;
	p1=NULL;
	printf("1.票价从低向高\t2.票价从高到低\n");
	printf("请选择排序方式:");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			while((list->next->next)!=p1)              //循环 
			{
				p=list;
				q=list->next;
				while(q->next!=p1)
				{
					if(q->price>q->next->price)
					{
						p->next=q->next;                       //节点交换 
						q->next=q->next->next;
						p->next->next=q;
						q=p->next;
					}
					q=q->next;
					p=p->next;
				}
				p1=q;
			}
			printf("---【排序已经完成】---\n");
			break;
		case 2:
		    while((list->next->next)!=p1)
			{
				p=list;
				q=list->next;
				while(q->next!=p1)
				{
					if(q->price<q->next->price)
					{
						p->next=q->next;
						q->next=q->next->next;
						p->next->next=q;
						q=p->next;
					}
					q=q->next;
					p=p->next;
				}
				p1=q;
			}
			printf("---【排序已经完成】---\n");
			break;
		default:
			printf("---【输入异常！！！请重新输入】---\n");
			break;
	}
}

//浏览电影信息
void output(Linklist *p)
{
	system("cls");
	printf("*********************************************************\n");
	printf("*\t\t   影院影片列表     \t\t\t*\n");
	printf("*********************************************************\n");
	printf("*编号\t名称\t票价\t观看人次\t出版公司\t*\n");
	while(p->next!=NULL)                                                            //遍历链表 
	{
		p=p->next;
		printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",p->number,p->name,p->price,p->people,p->publish);
	}
	printf("*********************************************************\n\n");
}

//打印电影信息
void printfs(Linklist *p)
{
	Linklist *pm;
	system("cls");
	printf("*********************************************************\n");
	printf("*\t\t   影院影片列表     \t\t\t*\n");
	printf("*********************************************************\n");
	printf("*编号\t名称\t票价\t观看人次\t出版公司\t*\n");
	for(pm=p->next;pm->next!=NULL;pm=pm->next)                                                            //遍历链表 
	{
		printf("*%s\t%s\t%d\t%d\t\t%s\t\t*\n",pm->number,pm->name,pm->price,pm->people,pm->publish);
	}
	printf("*********************************************************\n\n");
}


//主函数 
int main()
{
	int i=5,shuru;
	Linklist *p1;
	char c[]={"200108"};
	char s[20];
	while(i)
	{
		printf("请输入登录密码:");
		scanf("%s",s);
		if(!strcmp(s,c))                                //字符串的比较，在查询功能中起到了作用 
		{
	        system("cls");                          //清屏，没有这个会重复出现目录界面 
			do
			{
			    menu();                                                     //菜单函数 
		        scanf("%d",&shuru);
		        switch(shuru)
				{
			        case 1:
					    printf("---【录入电影信息】---\n");
			            p1=input();
			            break;	
		            case 2:
		    	        printf("---【修改电影信息】---\n");
		              	change(p1);
		            	break;
		            case 3:
		            	printf("---【删除电影信息】---\n");
	            		delete(p1);
		            	break;
	            	case 4:
	            		printf("---【查询电影信息】---\n");
		            	search(p1);
		            	break;
	            	case 5:
		            	printf("---【电影信息排序】---\n");
		            	sort(p1); 
		            	break;
	            	case 6:
		            	printf("---【统计电影信息】---\n");
		            	statist(p1);
		            	break;
	            	case 7:
		             	printf("---【插入电影信息】---\n");
		            	insert(p1);
		            	break;
	            	case 8:
		            	printf("---【浏览电影信息】---\n");
		    	        output(p1);
        		    	break;
	            	case 0:
	             		printf("---【已经安全退出系统】---\n");
	            		break;
	            	default:
		            	printf("---【输入异常！！！请重新输入】---\n");
		            	break; 
	            }
	            system("pause");                        //暂停 
	            system("cls");                          //清屏，没有这个会重复出现目录界面 
	        }
        	while(shuru!=0);               //循环 
	        return 0; 
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
