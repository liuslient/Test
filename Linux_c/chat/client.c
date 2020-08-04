#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<signal.h>
#include<sys/epoll.h>
#include"chat.h"

#define SERV_PORT 8848  

#define EXIT -1
#define REGISTE 1
#define LOGIN 2

#define PASSIVE 0
#define ACTIVE 1

void *get_back(void *arg);
int login_menu();       
int login();            
void registe();
void Menu();    
void Menu_friends();
void look_fri();
void add_fri();
void del_fri();
void shi_fri();
void rel_fri();
void chat_one();


int sock_fd;
pthread_mutex_t mutex;
pthread_cond_t cond;
char user[MAX_CHAR];
FRI_INFO fri_info;
GROUP_INFO grp_info;
RECORD_INFO rec_info[55];

char name[100][MAX_CHAR];
char mes_box[100][MAX_CHAR];
int mes_box_inc[100];
int sign;
int sign_ive[100];

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    pthread_t thid;

    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);

    if(connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0)
        my_err("connect",__LINE__);
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    if(login_menu() == 0)
    {
        close(sock_fd);
        return 0;
    }

    pthread_create(&thid, NULL, get_back, NULL);
    
    Menu();

    close(sock_fd);

    return 0;
}

void *get_back(void *arg)
{
	pthread_mutex_t mutex_g;
    pthread_mutex_init(&mutex_g, NULL);
    while(1)
    {
    	int flag;
        PACK recv_pack;
        int i = 0;
        int fd;
        int ret = recv(sock_fd, &recv_pack, sizeof(PACK), MSG_WAITALL);
        if(ret < 0)
            my_err("recv", __LINE__);
            
        switch(recv_pack.type)
        {
        	case LOOK_FRI:
                memcpy(&fri_info, &recv_pack.fri_info, sizeof(FRI_INFO));
                pthread_cond_signal(&cond);           
                break;

            case GET_FRI_STA:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\t\t        ***%s***\n",recv_pack.data.recv_user);
                else if(flag == 1)
                    printf("\t\t\e[1;32m        ***%s***\e[0m\n",recv_pack.data.recv_user);
            
                pthread_cond_signal(&cond);
                break;

            case ADD_FRI:
                printf("\n\t\t\e[1;33m您有新消息\e[0m\n");
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                {
                    sign_ive[sign] = PASSIVE;
                    sprintf(name[sign], "%s", recv_pack.data.send_user);
                    mes_box_inc[sign] = ADD_FRI;
                    sprintf(mes_box[sign], "%s请求加你为好友(y/n): ", recv_pack.data.send_user);
                    sign++;
                }
                else if(flag == 1)
               {
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "%s已同意请求", recv_pack.data.send_user);
                    sign++;
               }
                else if(flag == 2)
                {
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "%s拒绝了你的请求", recv_pack.data.send_user);
                    sign++;
                }
                else if(flag == 3)
                {
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "%s账号不存在", recv_pack.data.send_user);
                    sign++;
                }
                else if(flag == 4)
                {
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "%s已是你的好友", recv_pack.data.send_user);
                    sign++;
                }
                break;

            case DEL_FRI:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t他不是你的好友!\n");
                else if(flag == 1)
                    printf("\n\t\t删除成功!\n");
            
                pthread_cond_signal(&cond);
                break;

            case SHI_FRI:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t他不是你的好友!\n");
                else if(flag == 1)
                    printf("\n\t\t屏蔽成功!\n");
            
                pthread_cond_signal(&cond);
                break;
                
            case REL_FRI:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t他不是你的好友!\n");
                else if(flag == 1)
                    printf("\n\t\t解除屏蔽成功!\n");
            
                pthread_cond_signal(&cond);
                break;
                
            case CHAT_ONE:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                {
                    printf("\n\t\t该用户不存在!\n");
					pthread_cond_signal(&cond);           
                }
                else if(flag == 1)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "好友%s想要与你聊天...", recv_pack.data.send_user);
                    sign++;
                }
                else if(flag == 2)
                {
                    printf("\n\t\t该用户不在线!\n");
                    pthread_cond_signal(&cond);           
                }
                else if(flag == 3)
                {
                    printf("\n\t\t该好友被屏蔽!\n");
                    pthread_cond_signal(&cond);           
                }
                else if(flag == 6)
                {
                    memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                    pthread_cond_signal(&cond);           
                }
                else
                    printf("\n\t\t\e[1;34m%s\n\t\t%s:\e[0m %s\n", recv_pack.data.recv_user, recv_pack.data.send_user, recv_pack.data.mes);
                break;
                
		}
	}
}

void send_pack(int type, char *send_name, char *recv_name, char *mes)
{
    PACK pack_send;
    memset(&pack_send, 0, sizeof(PACK));
    pack_send.type = type;
    pack_send.data.recv_fd = sock_fd;
    strcpy(pack_send.data.send_user, send_name);
    strcpy(pack_send.data.recv_user, recv_name);
    strcpy(pack_send.data.mes, mes);
    if(send(sock_fd, &pack_send, sizeof(PACK), 0) < 0)
        my_err("send",__LINE__);
}

int login_menu()
{
    int choice;
    int flag;
    do
    {
        printf("\n\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t\033[;34m\33[1m*\033[0m        1.登陆               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        2.注册               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        0.退出               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\tchoice：");
        scanf("%d",choice);
        switch(choice)
        {  
            case 1:
                if(login() == 1)
                    return 1;
                break;
            case 2:
                registe();
                break;
            default:
                break;
        }
    }while(choice!=0);
    flag = EXIT;
    send_pack(flag, user, "server", " ");
    return 0;
} 


void registe()
{
    int flag = REGISTE;
    char registe_name[MAX_CHAR];
    char registe_passwd[MAX_CHAR];
    PACK recv_registe;
    int recv_registe_flag;

    printf("\t\t输入你想要注册账号的名称：");
    scanf("%s",registe_name);
    printf("\t\t输入你想要注册账号的密码：");
    scanf("%s",registe_passwd);
    
    send_pack(flag, registe_name, "server", registe_passwd);
    if(recv(sock_fd, &recv_registe, sizeof(PACK), MSG_WAITALL) < 0)
        my_err("recv", __LINE__);
    recv_registe_flag = recv_registe.data.mes[0] - '0';

    if(recv_registe_flag == 1)
        printf("\t\t注册成功!\n");
    else
    {
        printf("\t\t该用户名已存在，请重新输入\n");
    } 
}

int login()
{
    int flag = LOGIN;
    char login_name[MAX_CHAR];
    char login_passwd[MAX_CHAR];
    PACK recv_login;
    int recv_login_flag;
    int i = 0;

    printf("\t\t请输入账号名称：");
    scanf("%s",login_name);
    getchar();                          
    printf("\t\t请输入账号密码：");
    scanf("%s",login_passwd);
    system("clear");
    send_pack(flag, login_name, "server", login_passwd);
    if(recv(sock_fd, &recv_login, sizeof(PACK), MSG_WAITALL) < 0)
        my_err("recv", __LINE__);
    
    recv_login_flag = recv_login.data.mes[0] - '0';

    if(recv_login_flag == 1)
    {
        printf("\t\t登陆成功!\n");
        strncpy(user, login_name, strlen(login_name));
        return 1;
    }
    else 
    {
	    printf("\t\t登陆失败!\n");
    } 
	return 0;
}


void Menu()
{
    int choice;
    int flag;
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         1.好友管理        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.注销            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",choice);
        
        switch(choice)
        {
        case 1:
            Menu_friends();
            break;
        
        default:
            break;
        }
    }while(choice != 0);
    flag = EXIT;
    send_pack(flag, user, "server", " ");
}

void Menu_friends()
{
    int choice;
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         1.查看好友        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         2.添加好友        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         3.删除好友        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         4.屏蔽好友        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         5.解除屏蔽好友    \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         6.私聊            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.返回            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",choice);
        
        switch(choice)
        {
        case 1:
            look_fri();
            break;

        case 2:
            add_fri();
            break;
           
        case 3:
            del_fri();
            break;

        case 4:
            shi_fri();
            break;
            
        case 5:
        	rel_fri();
        	break;

        case 6:
            chat_one();
            break; 
            

        default:
            break;
        }
    }while(choice != 0);
}

void look_fri()
{
    int flag = LOOK_FRI;
    char mes[MAX_CHAR];
    bzero(mes, MAX_CHAR);
    memset(&fri_info, 0, sizeof(fri_info));
    int i;

    pthread_mutex_lock(&mutex);
    send_pack(flag, user, "server", "1");
    pthread_cond_wait(&cond, &mutex);
    printf("\n\t\t\e[1;34m***********朋友列表***********\e[0m\n");
    if(fri_info.friends_num == 0)
        printf("\t\t暂无好友!\n");
    else
    {
        for(i = 0; i < fri_info.friends_num; i++)
        {
            if(fri_info.friends_status[i] == 1)
            {
                flag = GET_FRI_STA;
                send_pack(flag, fri_info.friends[i], "server", mes);
                pthread_cond_wait(&cond, &mutex);
            }
            else if(fri_info.friends_status[i] == 2)
                printf("\t\t\e[1;31m        ***%s***\e[0m\n",fri_info.friends[i]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void add_fri()
{
    int i;
    int flag = ADD_FRI;
    pthread_mutex_lock(&mutex);
    char friend[MAX_CHAR];
    printf("\t\t你想要添加的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, friend, "0");
    pthread_mutex_unlock(&mutex);
}

void del_fri()
{
    int flag = DEL_FRI;
    char friend[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要删除的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, "server", friend);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void shi_fri()
{
    int flag = SHI_FRI;
    char friend[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要屏蔽的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, "server", friend);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void rel_fri()
{
	int flag = REL_FRI;
    char friend[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要解除屏蔽的好友名称：");
    scanf("%s",friend);
    send_pack(flag, user, "server", friend);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}


void chat_one()
{
    int flag = CHAT_ONE;
    char chat_name[MAX_CHAR];
    char mes[MAX_CHAR];
    int i = 0;
    memset(mes, 0, sizeof(mes));
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].messages[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入聊天对象的名字 ");
    scanf("%s",chat_name);
    mes[0] = '1';
    send_pack(flag, user, chat_name, mes);
    
    pthread_cond_wait(&cond, &mutex);
    printf("\n\t\t\e[1;34m***********Message***********\e[0m\n");
    if(rec_info[0].messages[0] == '0')
        printf("\t\t暂无未读消息\n");
    else
    {
        while(rec_info[i].messages[0] != '0')
        {
            printf("\t\t\e[1;35m%s-->%s: \e[0m%s\n",rec_info[i].send_user, rec_info[i].recv_user, rec_info[i].messages);
            i++;
        }
    }
    printf("\n\t\t\e[1;33m按q退出聊天\e[0m\n");
    getchar();
    do
    {
        memset(mes, 0, sizeof(mes));
        printf("\t\t\e[1;34m%s:\e[0m ", user);
        scanf("%[^\n]", mes);
        getchar();
        send_pack(flag, user, chat_name, mes);
    }while(strcmp(mes, "q") != 0);

    pthread_mutex_unlock(&mutex);
}
