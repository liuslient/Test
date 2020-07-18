#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define PARAM_NONE   0                 //无参数
#define PARAM_A      1                 //-a  显示所有文件
#define PARAM_L      2                 //-l  显示一个文件的详细信息
#define PARAM_R      8                 //-R  
#define MAXROWLEN    80                //一行显示的最多字符数

int g_leave_len = MAXROWLEN;      //一行剩余长度，输出对齐    
int g_maxlen;                   //存放某目录最长文件名长度

unsigned long long sum;         

/*错误处理函数*/
void my_err(const char *err_string,int line)
{
	fprintf(stderr, "line:%d ", line);
	perror(err_string);
	exit(1);
}


/*获取文件属性并打印*/
void display_attribute(struct stat buf,char *name)
{
	char buf_time[32];
	struct passwd *psd;
	struct group *grp;

        /*获取打印文件类型*/
	if(S_ISLNK(buf.st_mode))
	{
		printf("l");
	}
	else if(S_ISREG(buf.st_mode))
	{
		printf("-");
	}
	else if(S_ISDIR(buf.st_mode))
        {
                printf("d");
        }
	else if(S_ISCHR(buf.st_mode))
        {
                printf("c");
        }
	else if(S_ISBLK(buf.st_mode))
        {
                printf("b");
        }
	else if(S_ISFIFO(buf.st_mode))
        {
                printf("f");
        }
	else if(S_ISSOCK(buf.st_mode))
        {
                printf("s");
        }

        /*获取打印文件所有者的权限*/
	if(buf.st_mode&S_IRUSR)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if(buf.st_mode&S_IWUSR)
        {
                printf("w");
        }
        else
        {
                printf("-");
        }
	if(buf.st_mode&S_IXUSR)
        {
                printf("x");
        }
        else
        {
                printf("-");
        }

        /*获取打印与文件所有者同组用户的操作权限*/
	if(buf.st_mode&S_IRGRP)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if(buf.st_mode&S_IWGRP)
        {
                printf("w");
        }
        else
        {
                printf("-");
        }
	if(buf.st_mode&S_IXGRP)
        {
                printf("x");
        }
        else
        {
                printf("-");
        }

        /*获取打印其他用户对该文件的操作权限*/
	if(buf.st_mode&S_IROTH)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if(buf.st_mode&S_IWOTH)
        {
                printf("w");
        }
        else
        {
                printf("-");
        }
	if(buf.st_mode&S_IXOTH)
        {
                printf("x");
        }
        else
        {
                printf("-");
        }

	printf("        ");

        /*通过uid与gid获取文件所有者的用户名和组名*/
	psd=getpwuid(buf.st_uid);
	grp=getgrgid(buf.st_gid);
	printf("%4ld ",buf.st_nlink);   //打印文件链接数
	printf("%-8s",psd->pw_name);    //打印用户名字
	printf("%-8s",grp->gr_name);    //打印用户组名字

	printf("%6ld  ",buf.st_size);     //打印文件大小
	sum = sum + buf.st_size;
	strcpy(buf_time,ctime(&buf.st_mtime));
	buf_time[strlen(buf_time)-1]='\0';//去掉换行符
	printf("  %s  ",buf_time);        //打印文件时间信息
}



//输出文件名若命令无-l，输出要上下对齐
void display_single(char *name)
{
	int i,len;
        //空间不足，进行换行
	if(g_leave_len<g_maxlen)
	{
		printf("\n");
		g_leave_len=MAXROWLEN;
	}

	len=g_maxlen-strlen(name);
	printf(" %-s",name);

	for(i=0;i<len;i++)
	{
		printf(" ");
	}
	printf(" ");
	//下面两指示空两格
	g_leave_len -=(g_maxlen+2);
}



//根据命令行参数与路径名显示文件信息
void display(int flag,char *pathname)
{
	int i,j;
	struct stat buf;
	char  name[NAME_MAX+1];

	//解析文件名
	for(i=0,j=0;i<strlen(pathname);i++)
	{
		if(pathname[i]=='/')
		{
			j=0;
			continue;
		}
		name[j++]=pathname[i];
	}
	name[j]='\0';

	//解析链接文件
	if(lstat(pathname,&buf)==-1)
	{
		my_err("stat",__LINE__);
	}

	switch(flag)
	{
		case PARAM_NONE:                                     //无选项
			if(name[0]!='.')
			{
				display_single(name);
			}
			break;

		case PARAM_A:                                        // -a
                        display_single(name);
                        break;

		case PARAM_L:                                        // -l
                        if(name[0]!='.')
                        {
                                display_attribute(buf,name);
				printf("%-s\n",name);
                        }
                        break;

		case PARAM_R:                                        // -R
                      if(name[0]!='.') 
		      {
			      display_single(name);
		      }
                       break;

		case PARAM_A+PARAM_L:                                // -a与-l
                        display_attribute(buf,name);
			printf("%-s\n",name);
                        break;

		case PARAM_A+PARAM_R:                                // -a与-R
                        display_single(name);
                        break;

		case PARAM_R+PARAM_L:                                //-R与-l
                        if(name[0]!='.')
                        {
                                display_attribute(buf,name);
                                printf("%-s\n",name);
                        }
                        break;

		case PARAM_A+PARAM_L+PARAM_R:                        //-a与-R与-l
                        display_attribute(buf,name);
                        printf("%-s\n",name);
                        break;

		default:
			break;
	}
}

//为显示某个目录下的文件做准备
void display_dir(int flag_param,char *path)
{
	DIR  *dir;
	struct dirent  *ptr;
	int count=0;
	char temp[PATH_MAX+10];

	//获取该目录下文件总数与最长的文件名
	dir=opendir(path);

	if(dir==NULL)
	{
		my_err("opendir",__LINE__);
	}

	while((ptr=readdir(dir))!=NULL)
	{
		if(g_maxlen<strlen(ptr->d_name))
		{
			g_maxlen=strlen(ptr->d_name);
		}
		count++;
	}


	//开辟空间
	char **filenames = (char **)malloc(sizeof(char*)*(count+1));
        for(int i = 0;i < count+1;i++)
	{
		filenames[i] = (char *)malloc(sizeof(int)*10000);
        }

	closedir(dir);

	int i,j,len=strlen(path);
	//获取该目录下所有的文件名
	dir=opendir(path);
	for(i=0;i<count;i++)
	{
		ptr=readdir(dir);
		if(ptr==NULL)
		{
			my_err("readdir",__LINE__);
		}
		strncpy(filenames[i],path,len);
		filenames[i][len]='\0';
		strcat(filenames[i],ptr->d_name);
		filenames[i][len+strlen(ptr->d_name)]='\0';

	}
	

	//冒泡排序对文件名，将名字存储在filenames里
	for(i=0;i<count-1;i++)
	{
		for(j=0;j<count-1-i;j++)
		{
			if(strcmp(filenames[j],filenames[j+1])>0)
			{
				strcpy(temp,filenames[j+1]);
				temp[strlen(filenames[j+1])]='\0';
				strcpy(filenames[j+1],filenames[j]);
				filenames[j+1][strlen(filenames[j])]='\0';
				strcpy(filenames[j],temp);
				filenames[j][strlen(temp)]='\0';
			}
		}
	}
	for(i=0;i<count;i++)
	{
		display(flag_param,filenames[i]);
	}

	//递归读取某文件夹及其子文件夹下所有文件名
	if(flag_param & PARAM_R)
	{
		rewinddir(dir);//倒带目录：返回最开始的位置
		
		//对文件名进行排序，存储到filenames里
		for(i = 0;i < count-1;i++)
		{
			for(j = 0;j < count-1-i;j++)
			{
				if(strcmp(filenames[j],filenames[j+1]) > 0)
				{
					strcpy(temp,filenames[j+1]);
                                        temp[strlen(filenames[j+1])] = '\0';
                                        strcpy(filenames[j+1],filenames[j]);
                                        filenames[j+1][strlen(filenames[j])] = '\0';
                                        strcpy(filenames[j],temp);
                                        filenames[j][strlen(temp)] = '\0';
                                 }
                        }
                }

		//读取dir目录信息，判断是否为空
		while((ptr=readdir(dir))!=NULL)
		{
			char path2[_PC_PATH_MAX+1];
                        strcpy(path2,path);//拷贝字符串

                        path2[strlen(path2)+1]='\0';
                        strcat(path2,ptr->d_name);//把字符串连接到数组末尾

            
                        path2[strlen(path2)]='\0';
                        struct stat buf2;
                        lstat(path2,&buf2);//解析链接文件
			
			if(strcmp(ptr->d_name,"..")!=0 && strcmp(ptr->d_name,".")!=0 && S_ISDIR(buf2.st_mode)) //判断是否是一个目录和是否是开始目录
			{
				putchar('\n');
                                char path2[_PC_PATH_MAX+1];
                                strcpy(path2,path);

                                path2[strlen(path2)+1]='\0';
                                strcat(path2,ptr->d_name);//把字符串连接到数组末尾

				strcat(path2,"/");
				strcat(path2,"\0");
                
                                printf("%s\n",path2);
                                display_dir(flag_param,path2);//递归使用
                       }
                 }
	}
	
	closedir(dir);//关闭dir所指向的目录
	//命令行无-l，打印一个换行符
	if((flag_param&PARAM_L)==0)
	{
		printf("\n");
	}
}



/*主函数*/
int main(int argc,char **argv)
{
	int i,j,k,num;
	char path[PATH_MAX+1];
	char param[32];                        //保存命令行参数
	int flag_param=PARAM_NONE;             //参数种类
	struct stat buf;

	//命令行参数解析
	j=0;
	num=0;
	for(i=0;i<argc;i++)
	{
		if(argv[i][0]=='-')
		{
			for(k=1;k<strlen(argv[i]);k++,j++)
			{
				param[j]=argv[i][k];
			}
			num++;
		}
	}

	//只支持参数a，R，l，其他就报错
	for(i=0;i<j;i++)
	{
		if(param[i]=='a')
		{
			flag_param |=PARAM_A;
			continue;
		}
		else if(param[i]=='l')
		{
			flag_param |=PARAM_L;
			continue;
		}
		else if(param[i]=='R')
                {
                        flag_param |=PARAM_R;
                        continue;
                }
		else
		{
			printf("myls:invalid option -%c\n",param[i]);
			exit(1);
		}
	}
	param[j]='\0';

	//没有输入文件名，就显示当前目录
	if((num+1)==argc)
	{
		strcpy(path,"./");
		path[2] = '\0';
		display_dir(flag_param,path);
		return 0;
	}

	i=1;
	/*访问proc时出现了No such file or directory的问题*/
	while(i<argc)
	{
		//如果不是目标文件名或目录，解析下一个命令行参数
		if(argv[i][0]=='-')
		{
			i++;
                        continue;
                }
		else
		{
			int ii = i;
			strcpy(path,argv[i]);
			//目标文件不存在报错退出
			if(stat(path,&buf)==-1)
                        {
				my_err("stat",__LINE__);
                        }
                        if(S_ISDIR(buf.st_mode))
                        {
				char a = path[strlen(argv[ii])-1];
				if(path[strlen(argv[ii])-1]!='/')
                                {
					path[strlen(argv[ii])]='/';
                                        path[strlen(argv[ii])+1]='\0';
				}
                                else
				{
					path[strlen(argv[ii])]='\0';
                                }
				display_dir(flag_param,path);
			}
			else
			{
				display(flag_param,path);//参数为一个文件
                        }
			i++;
		}
	}
	return 0;
}
