#include"client.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    pthread_t pid;

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

    pthread_create(&pid, NULL, recv_back, NULL);
    
    Menu();

    close(sock_fd);

    return 0;
}

void *recv_back(void *arg)
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
            
        if(ret == 0)
        {
            printf("\n\t\t\e[1;31m服务器崩溃，客户端退出\e[0m\n");
            exit(1);
        }

        switch(recv_pack.type)
        {
        case LOOK_FRI:
            memcpy(&fri_info, &recv_pack.fri_info, sizeof(FRI_INFO));
            pthread_cond_signal(&cond);           
            break;

        case GET_FRI_STA:
            flag = recv_pack.data.mes[0] - '0';
            if(flag == 0)
                printf("\t\t        ***%s***\n",recv_pack.data.recv_name);
            else if(flag == 1)
                printf("\t\t\e[1;32m        ***%s***\e[0m\n",recv_pack.data.recv_name);
            
            pthread_cond_signal(&cond);
            break;

        case ADD_FRI:
            printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
            printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
            flag = recv_pack.data.mes[0] - '0';
            if(flag == 0)
            {
                sign_ive[sign] = PASSIVE;
                sprintf(name[sign], "%s", recv_pack.data.send_name);
                mes_box_inc[sign] = ADD_FRI;
                sprintf(mes_box[sign], "%s请求加你为好友(y/n): ", recv_pack.data.send_name);
                sign++;
            }
            else if(flag == 1)
            {
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "%s已同意请求", recv_pack.data.send_name);
                sign++;
            }
            else if(flag == 2)
            {
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "%s拒绝了你的请求", recv_pack.data.send_name);
                sign++;
            }
            else if(flag == 3)
            {
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "%s账号不存在", recv_pack.data.send_name);
                sign++;
            }
            else if(flag == 4)
            {
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "%s已是你的好友", recv_pack.data.send_name);
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
            
        case CHAT_FRI:
            flag = recv_pack.data.mes[0] - '0';
            if(flag == 0)
            {
                printf("\n\t\t该用户不存在!\n");
                shi_flag = 1;
                pthread_cond_signal(&cond);           
            }
            else if(flag == 1)
            {
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "好友%s向你发送消息，请进入私聊功能查看", recv_pack.data.send_name);
                sign++;
            }
            else if(flag == 2)
            {
                printf("\n\t\t该用户不在线!\n");
                pthread_cond_signal(&cond);           
            }
            else if(flag == 3)
            {
                printf("\n\t\t该好友已被屏蔽!\n");
                shi_flag = 1;
                pthread_cond_signal(&cond);           
            }
            else if(flag == 6)
            {
                memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                pthread_cond_signal(&cond);           
            }
            else
                printf("\n\t\t\e[1;34m%s:\e[0m %s\n", recv_pack.data.send_name, recv_pack.data.mes);
            break;
            
        case CHECK_MES_FRI:
            flag = recv_pack.data.mes[0] - '0';
            if(flag == 0)
                printf("\t\t该用户不是你的好友\n");
            else if(flag == 1)
            {
                memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                printf("\n\t\t\e[1;34m***********聊天记录***********\e[0m\n");
                if(rec_info[0].message[0] == '0')
                printf("\t\t暂无历史记录\n");
                else
                {
                    while(rec_info[i].message[0] != '0')
                    {
                        printf("\t\t\e[1;35m%s = = >%s: \e[0m%s\n",rec_info[i].user, rec_info[i].other_user, rec_info[i].message);
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
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                bzero(grp_name, MAX_CHAR);
                strcpy(grp_name, recv_pack.file.mes);
                sign_ive[sign] = PASSIVE;
                sprintf(name[sign], "%s", recv_pack.data.recv_name);
                mes_box_inc[sign] = ADD_GRP;
                sprintf(mes_box[sign], "%s请求加入群聊%s(y/n): ", recv_pack.data.recv_name, recv_pack.file.mes);
                sign++;
            }
            else if(flag == 2)
            {
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "你已加入群聊%s", recv_pack.data.recv_name);
                sign++;
            }
            else if(flag == 3)
            {
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "加入群聊%s请求被拒绝", recv_pack.data.recv_name);
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

        case SET_GRP:
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
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "你被设置为群%s的管理员", recv_pack.data.send_name);
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
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "你被踢出群聊%s", recv_pack.data.send_name);
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

        case CHECK_MUM_GRP:
            memcpy(&fri_info, &recv_pack.fri_info, sizeof(FRI_INFO));
            pthread_cond_signal(&cond);           
            break;

        case CHAT_GRP:
            flag = recv_pack.data.mes[0] - '0';
            if(flag == 0)
            {
                printf("\n\t\t该群不存在!\n");
                shi_flag = 1;
                pthread_cond_signal(&cond);           
            }
            else if(flag == 1)
            {
                printf("\n\t\t\e[1;33m新消息(在未读消息里查看)\e[0m");
                printf("\n\t\t\e[1;33m按数字选择你需要的功能\e[0m\n");
                sign_ive[sign] = ACTIVE;
                sprintf(mes_box[sign], "有人进入群聊%s", recv_pack.data.send_name);
                sign++;
            }
            else if(flag == 2)
                printf("\n\t\t\e[1;33m群%s有新消息,请进入群聊功能查看\e[0m\n",recv_pack.data.send_name);
            else if(flag == 6)
            {
                memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                pthread_cond_signal(&cond);           
            }
            else
                printf("\n\t\t\e\t\t%s:\e[0m %s\n",recv_pack.data.send_name, recv_pack.data.mes);
            break;

        case CHECK_MES_GRP:
            flag = recv_pack.data.mes[0] - '0';
            if(flag == 0)
                printf("\t\t你不是该群成员\n");
            else if(flag == 1)
            {
                memcpy(&rec_info, &recv_pack.rec_info, sizeof(rec_info));
                printf("\n\t\t\e[1;34m***********聊天记录***********\e[0m\n");
                if(rec_info[0].message[0] == '0')
                printf("\t\t暂无历史记录\n");
                else
                {
                    while(rec_info[i].message[0] != '0')
                    {
                        printf("\t\t\e[1;35m%s = = >%s: \e[0m%s\n",rec_info[i].user, rec_info[i].other_user, rec_info[i].message);
                        i++;
                    }
                }
            }
            pthread_cond_signal(&cond);
            break;

        default:
            break;
        }
    }
}

int login_menu()
{
    int flag;
    char choice_s[100];
    int choice;
    do
    {
         printf("\n\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t\033[;34m\33[1m*\033[0m        1.登陆               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        2.注册               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        0.退出               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\tchoice：");
        scanf("%s",choice_s);
        choice = get_choice(choice_s);
        
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
        
    }while(choice != 0);
    flag = EXIT;
    send_pack(flag, user, "server", " ");
    return 0;
}

int get_choice(char *choice_t)
{
    int choice = 0;
    int i,j; 
    for(i = 0; i < strlen(choice_t); i++)
        if(choice_t[i] < '0' || choice_t[i] > '9')
            return -1;
    for(i = 0; i < strlen(choice_t); i++)
    {
        int t = 1;
        for(j = 1; j < strlen(choice_t)-i; j++)
        {
            t *= 10;
        }
        choice += t*(int)(choice_t[i] - 48);
    }
    return choice;
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
    else if(recv_registe_flag == 0)
        printf("\t\t该用户名已存在\n");
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
    else if(recv_login_flag == 0)
        printf("\t\t登陆失败!\n");
    else if(recv_login_flag == 2)
        printf("\t\t该用户已在线!\n");
    return 0;
}

void Menu()
{
    char choice_s[100];
    int choice;
    do
    {
        printf("\n\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\t\033[;34m\33[1m*\033[0m        1.查看好友           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        2.添加好友           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        3.删除好友           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        4.屏蔽好友           \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        5.私聊               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        6.解除屏蔽好友       \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        7.查看好友聊天记录   \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        8.查看所加群         \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        9.查看群中成员       \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        10.创建群            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        11.加群              \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        12.退群              \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        13.解散群            \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        14.设置管理员        \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        15.踢人              \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        16.群聊              \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        17.查看群聊天记录    \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        18.未读消息          \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*\033[0m        0.退出               \033[;34m\33[1m*\033[0m \n");
        printf("\t\t\033[;34m\33[1m*******************************\033[0m\n");
        printf("\t\tchoice：");
        scanf("%s",choice_s);
        choice = get_choice(choice_s);
        
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
            chat_fri();
            break;
            
        case 6:
        	rel_fri();
        	break;
        	
        case 7:
            check_mes_fri();
            break;
            
        case 8:
            check_grp();
            break;

        case 9:
            check_mum_grp();
            break;

        case 10:
            cre_grp();
            break;
           
        case 11:
            add_grp();
            break;

        case 12:
            del_grp();
            break;

        case 13:
            del_grp();
            break;

        case 14:
            set_grp();
            break;
           
        case 15:
            kick_grp();
            break;

        case 16:
            chat_grp();
            break;
            
        case 17:
		     check_mes_grp();
		     break;

        case 18:
            Menu_mes_box();
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
    printf("\n\t\t\e[1;34m***********好友列表***********\e[0m\n");
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
    char friend_1[MAX_CHAR];
    printf("\t\t输入要添加的好友名称：");
    scanf("%s",friend_1);
    send_pack(flag, user, friend_1, "0");
    pthread_mutex_unlock(&mutex);
}

void del_fri()
{
    int flag = DEL_FRI;
    char friend_2[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入要删除的好友名称：");
    scanf("%s",friend_2);
    send_pack(flag, user, "server", friend_2);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void shi_fri()
{
    int flag = SHI_FRI;
    char friend_3[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入要屏蔽的好友名称：");
    scanf("%s",friend_3);
    send_pack(flag, user, "server", friend_3);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void rel_fri()
{
	int flag = REL_FRI;
    char friend_4[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入要解除屏蔽的好友名称：");
    scanf("%s",friend_4);
    send_pack(flag, user, "server", friend_4);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void chat_fri()
{
    int flag = CHAT_FRI;
    char friend_name[MAX_CHAR];
    char mes[MAX_CHAR];
    int i = 0;
    memset(mes, 0, sizeof(mes));
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].message[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入要聊天好友名称：");
    scanf("%s",friend_name);
    mes[0] = '1';
    send_pack(flag, user, friend_name, mes);
    
    pthread_cond_wait(&cond, &mutex);
    if(shi_flag == 1)
    {
        shi_flag = 0;
        pthread_mutex_unlock(&mutex);
        return;
    }
    printf("\n\t\t\e[1;34m***********消息***********\e[0m\n");
    if(rec_info[0].message[0] == '0')
        printf("\t\t暂无未读消息\n");
    else
    {
        while(rec_info[i].message[0] != '0')
        {
            printf("\t\t\e[1;35m%s = = >%s: \e[0m%s\n",rec_info[i].user, rec_info[i].other_user, rec_info[i].message);
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
        send_pack(flag, user, friend_name, mes);
    }while(strcmp(mes, "q") != 0);

    pthread_mutex_unlock(&mutex);
}

void check_mes_fri()
{
    int i = 0;
    int flag = CHECK_MES_FRI;
    char fri_4[MAX_CHAR];
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].message[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入想要查看聊天记录的好友昵称：");
    scanf("%s",fri_4);
    send_pack(flag, user, "server", fri_4);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
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
    printf("\n\t\t\e[1;34m***********群列表***********\e[0m\n");
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

void check_mum_grp()
{
    int flag = CHECK_MUM_GRP;
    char mes[MAX_CHAR];
    int i;

    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入要查看群成员的群名称：");
    scanf("%s",mes);
    for(i = 0; i < grp_info.grp_num; i++)
    {
        if(strcmp(grp_info.groups[i], mes) == 0)
            break;
    }
    if(i >= grp_info.grp_num)
        printf("\t\t你没有加入此群!\n");
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
    char grp_1[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入想要创建的群名称：");
    scanf("%s",grp_1);
    send_pack(flag, user, "server", grp_1);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void add_grp()
{
    int flag = ADD_GRP;
    char grp_2[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入想要加入的群名称：");
    scanf("%s",grp_2);
    send_pack(flag, user, "server", grp_2);
    pthread_mutex_unlock(&mutex);
}

void out_grp()
{
    int flag = OUT_GRP;
    char grp_3[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入想要退出的群名称：");
    scanf("%s",grp_3);
    send_pack(flag, user, "server", grp_3);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}


void del_grp()
{
    int flag = DEL_GRP;
    char grp_4[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入想要解散的群名称：");
    scanf("%s",grp_4);
    send_pack(flag, user, "server", grp_4);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void set_grp()
{
    int flag = SET_GRP;
    char grp[MAX_CHAR];
    char grp_user[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入要在进行操作的群昵称：");
    scanf("%s",grp);
    printf("\t\t输入想要设为管理员的昵称："); 
    scanf("%s",grp_user);
    send_pack(flag, user, grp, grp_user);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void kick_grp()
{
    int flag = KICK_GRP;
    char grp[MAX_CHAR];
    char grp_user[MAX_CHAR];
    pthread_mutex_lock(&mutex);
    printf("\t\t输入要进行操作的群昵称：");
    scanf("%s",grp);
    printf("\t\t输入要踢出人的昵称："); 
    scanf("%s",grp_user);
    send_pack(flag, user, grp, grp_user);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void chat_grp()
{
    int flag = CHAT_GRP;
    char chat_name[MAX_CHAR];
    char mes[MAX_CHAR];
    int i = 0;
    memset(mes, 0, sizeof(mes));
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].message[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入想要聊天的群昵称：");
    scanf("%s",chat_name);
    mes[0] = '1';
    send_pack(flag, user, chat_name, mes);
    
    pthread_cond_wait(&cond, &mutex);
    if(shi_flag == 1)
    {
        shi_flag = 0;
        pthread_mutex_unlock(&mutex);
        return;
    }
    printf("\n\t\t\e[1;34m***********消息***********\e[0m\n");
    if(rec_info[0].message[0] == '0')
        printf("\t\t暂无消息\n");
    else
    {
        while(rec_info[i].message[0] != '0')
        {
            printf("\t\t\e[1;35m%s = = >%s: \e[0m%s\n",rec_info[i].user, rec_info[i].other_user, rec_info[i].message);
            i++;
        }
    }
    printf("\n\t\t\e[1;33m按q退出群聊\e[0m\n");
    getchar();
    do
    {
        memset(mes, 0, sizeof(mes));
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
    char grp_5[MAX_CHAR];
    memset(&rec_info, 0, sizeof(rec_info));
    rec_info[0].message[0] = '0';
    pthread_mutex_lock(&mutex);
    printf("\n\t\t输入要查看聊天记录的群昵称：");
    scanf("%s",grp_5);
    send_pack(flag, user, "server", grp_5);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

void Menu_mes_box()
{
    int i;
    char ch[5];
    pthread_mutex_lock(&mutex);
    printf("\n\t\t%d条消息未读\n", sign);
    for(i = 0; i < sign; i++)
    {
        if(sign_ive[i] == PASSIVE)
        {
            printf("\t\t%d: %s", i + 1, mes_box[i]);
            scanf("%s", ch);
            if(mes_box_inc[i] == ADD_GRP)
                send_pack(mes_box_inc[i], grp_name, name[i], ch);
            else
                send_pack(mes_box_inc[i], user, name[i], ch);
        }
        else if(sign_ive[i] == ACTIVE)
            printf("\t\t%d: %s\n", i + 1, mes_box[i]);
    }
    sign = 0;
    pthread_mutex_unlock(&mutex);
}

void send_pack(int type, char *send_name, char *recv_name, char *mes)
{
    PACK pack_send;
    memset(&pack_send, 0, sizeof(PACK));
    pack_send.type = type;
    pack_send.data.recv_fd = sock_fd;
    strcpy(pack_send.data.send_name, send_name);
    strcpy(pack_send.data.recv_name, recv_name);
    strcpy(pack_send.data.mes, mes);
    if(send(sock_fd, &pack_send, sizeof(PACK), 0) < 0)
        my_err("send",__LINE__);
}
