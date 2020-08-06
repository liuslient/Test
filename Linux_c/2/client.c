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

#define MAX_FILE 100

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
void check_mes_fri();
void Menu_groups();
void check_grp_menu();
void check_grp();
void cre_grp();
void out_grp();
void power_grp_menu(); 
void set_grp_adm();
void del_grp();
void kick_grp();
void chat_many();
void check_mes_grp();

void send_pack(int type, char *send_name, char *recv_name, char *mes);



int sock_fd;
pthread_mutex_t mutex;
pthread_cond_t cond;
char user[MAX_CHAR];
char grp_name[MAX_CHAR];
FRI_INFO fri_info;
GROUP_INFO grp_info;
RECORD_INFO rec_info[55];

char name[100][MAX_CHAR];
char mes_box[100][MAX_CHAR];
int mes_box_inc[100];
int sign;
int sign_ive[100];
int ffflag;

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
                
            case CHECK_MES_FRI:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\t\t该用户不是你的好友\n");
                else if(flag == 1)
                {
                    memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                    printf("\n\t\t\e[1;34m***********聊天记录***********\e[0m\n");
                    if(rec_info[0].messages[0] == '0')
                        printf("\t\t暂无历史记录\n");
                    else
                    {
                        while(rec_info[i].messages[0] != '0')
                        {
                            printf("\t\t\e[1;35m%s-->%s: \e[0m%s\n",rec_info[i].send_user, rec_info[i].recv_user, rec_info[i].messages);
                            i++;
                        }
                    }
                }
                pthread_cond_signal(&cond);
                break;
                
            case CRE_GRP:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t该群名已被注册!\n");
                else if(flag == 1)
                    printf("\n\t\t创建成功!\n");
                pthread_cond_signal(&cond);
                break;
        
            case ADD_GRP:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t该群不存在!\n");
                else if(flag == 1)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    bzero(grp_name, MAX_CHAR);
                    strcpy(grp_name, recv_pack.file.mes);
                    sign_ive[sign] = PASSIVE;
                    sprintf(name[sign], "%s", recv_pack.data.recv_user);
                    mes_box_inc[sign] = ADD_GRP;
                    sprintf(mes_box[sign], "%s请求加入群聊%s(y/n): ", recv_pack.data.recv_user, recv_pack.file.mes);
                    sign++;
                }
                else if(flag == 2)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "你已加入群聊%s", recv_pack.data.recv_user);
                    sign++;
                }
                else if(flag == 3)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "加入群聊%s请求被拒绝", recv_pack.data.recv_user);
                    sign++;
                }
                break;

            case OUT_GRP:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t该群不存在!\n");
                else if(flag == 1)
                    printf("\n\t\t退群成功!\n");
                pthread_cond_signal(&cond);
                break;

            case DEL_GRP:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t该群不存在!\n");
                else if(flag == 1)
                    printf("\n\t\t解散群成功!\n");
                else if(flag == 2)
                    printf("\n\t\t只有群主可以解散群!\n");
                pthread_cond_signal(&cond);
                break;

            case SET_GRP_ADM:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t该群不存在!\n");
                else if(flag == 1)
                    printf("\n\t\t设置管理员成功!\n");
                else if(flag == 2)
                    printf("\n\t\t只有群主可以设置管理员!\n");
                else if(flag == 3)
                    printf("\n\t\t此用户不在群中!\n");
                else if(flag == 6)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "你被设置为群%s的管理员", recv_pack.data.send_user);
                    sign++;
                    break;
                }
                if(flag != 6)
                    pthread_cond_signal(&cond);
                break;

            case KICK_GRP:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\n\t\t该群不存在!\n");
                else if(flag == 1)
                    printf("\n\t\t踢人成功!\n");
                else if(flag == 2)
                    printf("\n\t\t只有群主/管理员可以踢人!\n");
                else if(flag == 3)
                    printf("\n\t\t此用户不在群中!\n");
                else if(flag == 4)
                    printf("\n\t\t踢人失败!\n");
                else if(flag == 6)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "你被踢出群聊%s", recv_pack.data.send_user);
                    sign++;
                    break;
                }
                if(flag != 6)
                    pthread_cond_signal(&cond);
                break;

            case CHECK_GRP:
                memcpy(&grp_info, &recv_pack.grp_info, sizeof(GROUP_INFO));
                pthread_cond_signal(&cond);           
                break;

            case CHECK_MEM_GRP:
                memcpy(&fri_info, &recv_pack.fri_info, sizeof(FRI_INFO));
                pthread_cond_signal(&cond);           
                break;
            
            case CHAT_MANY:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                {
                    printf("\n\t\t该群不存在!\n");
                    ffflag = 1;
                    pthread_cond_signal(&cond);           
                }
                else if(flag == 1)
                {
                    printf("\n\t\t\e[1;33m您有新消息啦!\e[0m\n");
                    sign_ive[sign] = ACTIVE;
                    sprintf(mes_box[sign], "群%s有人进入群聊??", recv_pack.data.send_user);
                    sign++;
                }
                else if(flag == 2)
                    printf("\n\t\t\e[1;33m群%s有新消息\e[0m\n",recv_pack.data.send_user);
                else if(flag == 6)
                {
                    memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                    pthread_cond_signal(&cond);           
                }
                else
                    printf("\n\t\t\e[1;34m%s\n\t\t%s:\e[0m %s\n", recv_pack.data.recv_user, recv_pack.data.send_user, recv_pack.data.mes);
                break;
            
            case CHECK_MES_GRP:
                flag = recv_pack.data.mes[0] - '0';
                if(flag == 0)
                    printf("\t\t你不是该群成员\n");
                else if(flag == 1)
                {
                    memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                    printf("\n\t\t\e[1;34m***********His_Message***********\e[0m\n");
                    if(rec_info[0].messages[0] == '0')
                    printf("\t\t暂无历史记录\n");
                    else
                    {
                        while(rec_info[i].messages[0] != '0')
                        {
                            printf("\t\t\e[1;35m%s-->%s: \e[0m%s\n",rec_info[i].send_user, rec_info[i].recv_user, rec_info[i].messages);
                            i++;
                        }
                    }
                }
                pthread_cond_signal(&cond);
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
        scanf("%d",&choice);
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
    return 0;
} 


void registe()
{
    int flag = REGISTE;
    char registe_name[MAX_CHAR];
    char registe_passwd[MAX_CHAR];
    PACK recv_registe;
    int recv_registe_flag;

    printf("\t\t输入想要注册账号的名称：");
    scanf("%s",registe_name);
    printf("\t\t输入想要注册账号的密码：");
    scanf("%s",registe_passwd);
    
    send_pack(flag, registe_name, "server", registe_passwd);
    if(recv(sock_fd, &recv_registe, sizeof(PACK), MSG_WAITALL) < 0)
        my_err("recv", __LINE__);
    printf("这里没问题4\n");
    recv_registe_flag = recv_registe.data.mes[0] - '0';

    if(recv_registe_flag == 1)
        printf("\t\t注册成功!\n");
    else
    {
        printf("\t\t注册失败\n");
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
        printf("\t\t\e[1;32m|\e[0m         2.群管理          \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.注销            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
        switch(choice)
        {
        case 1:
            Menu_friends();
            break;
        
        case 2:
            Menu_groups();
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
        printf("\t\t\e[1;32m|\e[0m         7.聊天记录        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.返回            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
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
            
        case 7:
            check_mes_fri();
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

void check_mes_fri()
{
    int i = 0;
    int flag = CHECK_MES_FRI;
    char mes_fri[MAX_CHAR];
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].messages[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t你想要查看与谁的聊天记录? ");
    scanf("%s",mes_fri);
    send_pack(flag, user, "server", mes_fri);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void Menu_groups()
{
    int choice;
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         1.查看群          \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         2.创建群          \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         3.加群            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         4.退群            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         5.群管理          \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         6.群聊            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         7.聊天记录        \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.返回            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
        switch(choice)
        {
        case 1:
            check_grp_menu();           
            break;

        case 2:
            cre_grp();
            break;
           
        case 3:
            add_grp();
            break;

        case 4:
            out_grp();
            break;

        case 5:
            power_grp_menu();
            break;

        case 6:
            chat_many();
            break;
            
        case 7:
		     check_mes_grp();
		     break;

        default:
            break;
        }
    }while(choice != 0);
}

void check_grp_menu()
{
    int choice;
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         1.查看所加群      \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         2.查看群中成员    \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.返回            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
        switch(choice)
        {
        case 1:
            check_grp();
            break;

        case 2:
            check_mem_grp();
            break;

        default:
            break;
        }
    }while(choice != 0);
}

void check_grp()
{
    int flag = CHECK_GRP;
    char mes[MAX_CHAR];
    memset(mes, 0, sizeof(mes));
    memset(&grp_info, 0, sizeof(grp_info));
    int i;

    pthread_mutex_lock(&mutex);
    send_pack(flag, user, "server", mes);
    pthread_cond_wait(&cond, &mutex);
    printf("\n\t\t\e[1;34m***********群***********\e[0m\n");
    if(grp_info.grp_num == 0)
        printf("\t\t暂无加入群聊!\n");
    else
    {
        for(i = 0; i < grp_info.grp_num; i++)
        {
            printf("\t\t        ***%s***\n",grp_info.groups[i]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void check_mem_grp()
{
    int flag = CHECK_MEM_GRP;
    char mes[MAX_CHAR];
    int i;

    pthread_mutex_lock(&mutex);
    printf("\n\t\t你想要查看那个群中的成员信息：");
    scanf("%s",mes);
    for(i = 0; i < grp_info.grp_num; i++)
    {
        if(strcmp(grp_info.groups[i], mes) == 0)
            break;
    }
    if(i >= grp_info.grp_num)
        printf("\t\t你没有加入该群!\n");
    else
    {
        memset(&fri_info, 0, sizeof(fri_info));
        send_pack(flag, user, "server", mes);
        pthread_cond_wait(&cond, &mutex);
        printf("\n\t\t\e[1;34m***********%s***********\e[0m\n",mes);
        if(fri_info.friends_num == 0)
            printf("\t\t该群中暂无成员!\n");
        else
        {
            for(i = 0; i < fri_info.friends_num; i++)
                printf("\t\t        ***%s***\n", fri_info.friends[i]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void cre_grp()
{
    int flag = CRE_GRP;
    char grp_cre[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要创建的群名称：");
    scanf("%s",grp_cre);
    send_pack(flag, user, "server", grp_cre);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void add_grp()
{
    int flag = ADD_GRP;
    char grp_add[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要加入的群名称：");
    scanf("%s",grp_add);
    send_pack(flag, user, "server", grp_add);
    pthread_mutex_unlock(&mutex);
}

void out_grp()
{
    int flag = OUT_GRP;
    char grp_out[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要退出的群名称：");
    scanf("%s",grp_out);
    send_pack(flag, user, "server", grp_out);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void power_grp_menu()
{
    printf("\n\t\t\e[1;33m身为群主/管理员，你有以下特权：\e[0m\n");
    printf("\t\t\e[1;33m群主——1，2，3\e[0m\n");
    printf("\t\t\e[1;33m管理员——3\e[0m\n");
    int choice;
    do
    {
        printf("\n\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         1.解散群          \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         2.设置管理员      \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         3.踢人            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t\e[1;32m|\e[0m         0.返回            \e[1;32m|\e[0m\n");
        printf("\t\t\e[1;32m-----------------------------\e[0m\n");
        printf("\t\t请选择：");
        scanf("%d",&choice);
        
        switch(choice)
        {
        case 1:
            del_grp();
            break;

        case 2:
            set_grp_adm();
            break;
           
        case 3:
            kick_grp();
            break;

        default:
            break;
        }
    }while(choice != 0);
}

void del_grp()
{
    int flag = DEL_GRP;
    char grp_del[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要解散的群名称：");
    scanf("%s",grp_del);
    send_pack(flag, user, "server", grp_del);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void set_grp_adm()
{
    int flag = SET_GRP_ADM;
    char grp_set_1[MAX_CHAR];
    char grp_set_2[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要在那个群设置谁为管理员：");
    scanf("%s",grp_set_1);
    scanf("%s",grp_set_2);
    send_pack(flag, user, grp_set_1, grp_set_2);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void kick_grp()
{
    int flag = KICK_GRP;
    char grp_set_1[MAX_CHAR];
    char grp_set_2[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t你想要在那个群将谁踢出：");
    scanf("%s",grp_set_1);
    scanf("%s",grp_set_2);
    send_pack(flag, user, grp_set_1, grp_set_2);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void chat_many()
{
    int flag = CHAT_MANY;
    char chat_name[MAX_CHAR];
    char mes[MAX_CHAR];
    int i = 0;
    memset(mes, 0, sizeof(mes));
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].messages[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t你想要在那个群中聊天呢? ");
    scanf("%s",chat_name);
    mes[0] = '1';
    send_pack(flag, user, chat_name, mes);
    
    pthread_cond_wait(&cond, &mutex);
    if(ffflag == 1)
    {
        ffflag = 0;
        pthread_mutex_unlock(&mutex);
        return;
    }
    printf("\n\t\t\e[1;34m***********消息***********\e[0m\n");
    if(rec_info[0].messages[0] == '0')
        printf("\t\t暂无消息\n");
    else
    {
        while(rec_info[i].messages[0] != '0')
        {
            printf("\t\t\e[1;35m%s-->%s: \e[0m%s\n",rec_info[i].send_user, rec_info[i].recv_user, rec_info[i].messages);
            i++;
        }
    }
    printf("\n\t\t\e[1;33m按q退出群聊\e[0m\n");
    getchar();
    do
    {
        memset(mes, 0, sizeof(mes));
        scanf("%s", mes);
        scanf("%[^\n]", mes);
        getchar();
        send_pack(flag, user, chat_name, mes);
    }while(strcmp(mes, "q") != 0);

    pthread_mutex_unlock(&mutex);
}


void check_mes_grp()
{
    int i = 0;
    int flag = CHECK_MES_GRP;
    char mes_grp[MAX_CHAR];
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].messages[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t你想要查看那个群的聊天记录? ");
    scanf("%s",mes_grp);
    send_pack(flag, user, "server", mes_grp);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}
