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
#include<mysql.h>
#include<sys/epoll.h>
#include"chat.h"

#define SERV_PORT  8848  
#define LISTENQ    10     
#define MAX_EVENTS 1000

#define FRIEND    1
#define FRI_BLK   2
#define FRI_WHI   3 
#define GRP       4
#define GRP_OWN   5
#define GRP_ADM   6

#define OFFLINE   0
#define ONLINE    1
#define ONE_CHAT  2
#define MANY_CHAT 3

void *deal(void *recv_pack);
void Exit(PACK *recv_pack);   
void registe(PACK *recv_pack);
void login(PACK *recv_pack);
void look_fri(PACK *recv_pack);    
void get_fri_sta(PACK *recv_pack);  
void add_fri(PACK *recv_pack);      
void del_fri(PACK *recv_pack);    
void shi_fri(PACK *recv_pack);      
void rel_fri(PACK *recv_pack);     
void chat_one(PACK *recv_pack);  
void check_mes_fri(PACK *recv_pack);
void cre_grp(PACK *recv_pack);
void add_grp(PACK *recv_pack);
void out_grp(PACK *recv_pack);
void del_grp(PACK *recv_pack);
void set_grp_adm(PACK *recv_pack);
void kick_grp(PACK *recv_pack);
void check_grp(PACK *recv_pack);
void check_mem_grp(PACK *recv_pack);
void chat_many(PACK *recv_pack);
void check_mes_grp(PACK *recv_pack);
void send_file(PACK *recv_pack); 
void recv_file(PACK *recv_pack);

User *U_read();     
Relation *R_read();         
Recordinfo *RC_read();
void Insert(User *pNew);
void Insert_RC(Recordinfo *pNew);
void Insert_R(Relation *pNew);
void Delete_R(Relation *pNew);


MYSQL mysql;
pthread_mutex_t mutex;
pthread_cond_t cond;
User *pHead = NULL;
Relation *pStart = NULL;
Recordinfo *pRec = NULL;

PACK Mex_Box[100];
int sign;
int book;
File file;

int main()
{
	int i=0;
    int optval;
    char need[1000];
	int sock_fd,conn_fd;
	socklen_t len;
    struct sockaddr_in cli_addr,serv_addr;
    pthread_t pid;
    MYSQL_RES *result;
    
    PACK *pack;
    PACK recv_pack; 
    int ret;

    int epfd,nfds;   
    struct epoll_event ev, events[MAX_EVENTS];  
    len = sizeof(struct sockaddr_in);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    if (mysql_init(&mysql) == NULL) 
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    if (mysql_real_connect(&mysql,"127.0.0.1","root","new_password","chat",0,NULL,0) == NULL) 
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }
    
    mysql_set_character_set(&mysql,"utf8");

    printf("服务器启动中...\n");

    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);
    printf("创建套接字...\n");

    optval = 1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
        my_err("setsockopt",__LINE__);

    memset(&serv_addr,0,len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock_fd,(struct sockaddr *)&serv_addr,len) < 0)
        my_err("bind",__LINE__);
    printf("绑定端口...\n");

    if(listen(sock_fd,LISTENQ) < 0)
        my_err("listen",__LINE__);
    printf("侦听套接字...\n");

    epfd = epoll_create(MAX_EVENTS);   
    ev.data.fd = sock_fd;              
    ev.events = EPOLLIN;               
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd, &ev); 
    

    printf("服务器启动成功！\n");
    printf("等待客户端的接入中...\n");
    
    pHead = U_read();
    User *t = pHead;
    pStart = R_read();
    pRec = RC_read();

    while(1)
    {
        nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);    

        for(i = 0; i < nfds; i++)
        {
            if(events[i].data.fd == sock_fd)
            {
                conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr,&len);
                printf("Connected: %s, fd is %d\n",inet_ntoa(cli_addr.sin_addr), conn_fd);
                ev.data.fd = conn_fd;               
                ev.events = EPOLLIN;              
                epoll_ctl(epfd, EPOLL_CTL_ADD, conn_fd, &ev);  
                continue;
            }
            else if(events[i].events & EPOLLIN)
            {
                ret = recv(events[i].data.fd, &recv_pack, sizeof(PACK), MSG_WAITALL);
                recv_pack.data.send_fd = events[i].data.fd;

                if(ret < 0)
                {
                    close(events[i].data.fd);
                    perror("revc");
                    continue;
                }
                else if(ret == 0)
                {
                    ev.data.fd = events[i].data.fd;
                    while(t)
                    {
                        if(t->fd == ev.data.fd)
                        {
                            t->user_state = OFFLINE;
                            break;
                        }
                        t = t->next;
                    }
                    printf("fd: %d 的客户端退出\n",ev.data.fd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                    close(events[i].data.fd);
                    continue;
                }
				
				printf("\n\e[1;34m****PACK****\e[0m\n");
                printf("\e[1;34m*\e[0m type      : %d\n", recv_pack.type);
                printf("\e[1;34m*\e[0m send_fd   : %d\n", recv_pack.data.send_fd);
                printf("\e[1;34m*\e[0m recv_fd   : %d\n", recv_pack.data.recv_fd);
                printf("\e[1;34m*\e[0m send_user : %s\n", recv_pack.data.send_user);
                printf("\e[1;34m*\e[0m recv_user : %s\n",recv_pack.data.recv_user);
                printf("\e[1;34m*\e[0m mes       : %s\n", recv_pack.data.mes);
                printf("\e[1;34m*************\e[0m\n\n");
				

                pack= (PACK*)malloc(sizeof(PACK));
                memcpy(pack, &recv_pack, sizeof(PACK));
                if(pthread_create(&pid,NULL,deal,(void *)pack) != 0)
                    my_err("pthread_create",__LINE__);
            }
        }
    }
    free(pack);
    close(sock_fd);
    close(epfd);
    return 0;
}

void send_mes(int fd, int type, PACK *recv_pack, char *mes)
{
    PACK pack_send;
    char ss[MAX_CHAR];
    memcpy(&pack_send, recv_pack, sizeof(PACK));
    strcpy(ss,pack_send.data.recv_user);
    
    pack_send.type = type;
    strcpy(pack_send.data.recv_user, pack_send.data.send_user);
    strcpy(pack_send.data.send_user, ss);
    strcpy(pack_send.data.mes, mes);
    pack_send.data.recv_fd = pack_send.data.send_fd;
    pack_send.data.send_fd = fd;
    printf("skjafdg；%s\n",pack_send.data.mes);

    if(send(fd, &pack_send, sizeof(PACK), 0) < 0)
        my_err("send", __LINE__);
}

void send_pack(int fd, PACK *recv_pack, char *ch)
{
    PACK pack_send;
    memcpy(&pack_send, recv_pack, sizeof(PACK));
    strcpy(pack_send.data.recv_user, pack_send.data.send_user);
    strcpy(pack_send.data.send_user, "server");
    strcpy(pack_send.data.mes, ch);
    printf("%s\n", pack_send.data.mes);
    pack_send.data.send_fd = pack_send.data.recv_fd;
    pack_send.data.recv_fd = fd;
    printf("%d\n",fd); 
    if(send(fd, &pack_send, sizeof(pack_send), 0) < 0)
        my_err("send", __LINE__);
}

void *deal(void *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	printf("进入线程成功\n");
	printf("recv_pack : %d\n",recv_pack->type);
	switch(recv_pack->type)
	{
		case EXIT:
			Exit(recv_pack);
			break;
			
		case LOGIN:
			login(recv_pack);
			break;
			
		case REGISTE:
			registe(recv_pack);            
			break;
			
		case LOOK_FRI:
		    look_fri(recv_pack);
            break;

        case GET_FRI_STA:
            get_fri_sta(recv_pack);
            break;

        case ADD_FRI:
            add_fri(recv_pack);
            break;

        case DEL_FRI:
            del_fri(recv_pack);
            break;

        case SHI_FRI:
            shi_fri(recv_pack);
            break;
            
        case REL_FRI:
        	rel_fri(recv_pack);
        	break;
        	
        case CHAT_ONE:
            chat_one(recv_pack);
            break;
            
        case CHECK_MES_FRI:
            check_mes_fri(recv_pack);
            break;
            
        case CRE_GRP:
            cre_grp(recv_pack);
            break;

        case ADD_GRP:
           add_grp(recv_pack);
           break;

        case OUT_GRP:
            out_grp(recv_pack);
            break;

        case DEL_GRP:
            del_grp(recv_pack);
            break;

        case SET_GRP_ADM:
           set_grp_adm(recv_pack);
           break;

        case KICK_GRP:
           kick_grp(recv_pack);
           break;

        case CHECK_GRP:
           check_grp(recv_pack);
           break;

        case CHECK_MEM_GRP:
           check_mem_grp(recv_pack);
           break;
           
        case CHAT_MANY:
            chat_many(recv_pack);
            break;
  
        case CHECK_MES_GRP:
            check_mes_grp(recv_pack);
            break;
            
        case RECV_FILE:
            recv_file(recv_pack);
            break;

        case SEND_FILE:
            send_file(recv_pack);
            break;

		dafault:
			break;
	}
}

void Exit(PACK *recv_pack)
{
    User *t = pHead;
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
        {
            t->user_state = OFFLINE;
            break;
        }
        t = t->next;
    }
    close(recv_pack->data.send_fd);
}

void registe(PACK *recv_pack)
{
	char need[1000];
	char ch[5];
	int fd = recv_pack->data.send_fd;
	
	User *t = pHead;
    int flag = 0;
    User *pNew = (User *)malloc(sizeof(User));
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }
    
    if(flag == 0)
    {
        strcpy(pNew->nickname, recv_pack->data.send_user);
        strcpy(pNew->password, recv_pack->data.mes);
        pNew->user_state = OFFLINE;
        Insert(pNew);
        memset(need, 0, sizeof(need));
	    sprintf(need, "insert into user_data values('%s','%s')",  recv_pack->data.send_user, recv_pack->data.mes);
        printf("%s\n",need);
    	mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    else
        ch[0] = '0';
    
    ch[1] = '\0';
    printf("%d %d\n",recv_pack->data.recv_fd,recv_pack->data.send_fd); 
	send_pack(fd, recv_pack, ch);
}

void login(PACK *recv_pack)
{
	
	pthread_t pid1;
    pthread_t pid2;
	char ch[5];
    int fd = recv_pack->data.send_fd;
    int i;

    User *t = pHead;
    int flag = 0;
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0 && strcmp(t->password, recv_pack->data.mes) == 0)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }

    if(flag == 0)
        ch[0] = '0';
    else
    {
        if(t->user_state == OFFLINE)
        {
            ch[0] = '1';
            t->user_state = ONLINE;
            t->fd = recv_pack->data.send_fd;
        }
        else 
            ch[0] = '2';
    }
    ch[1] = '\0';
    printf("%d",t->user_state);
    printf("登录信息\n");
    send_pack(fd, recv_pack, ch);
    printf("发送成功你的登录信息\n");
    
    
    for(i = 0; i < sign; i++)
    {
        if((ch[0] == '1') && strcmp(recv_pack->data.send_user, Mex_Box[i].data.recv_user) == 0 && (Mex_Box[i].type == CHAT_ONE))
        {
            send_mes(fd, CHAT_ONE, &Mex_Box[i], "1");
            book++;
        }
        if((ch[0] == '1') && strcmp(recv_pack->data.send_user, Mex_Box[i].data.send_user) == 0 && (Mex_Box[i].type == CHAT_MANY))
        {
            send_mes(fd, CHAT_MANY, &Mex_Box[i], "2");
            book++;
        }
        if((ch[0] == '1') && strcmp(recv_pack->data.send_user, Mex_Box[i].data.recv_user) == 0 && (Mex_Box[i].type == ADD_FRI))
        {
			if(pthread_create(&pid1,NULL,deal,(void *)&Mex_Box[i]) != 0)
                my_err("pthread_create",__LINE__);  
            book++;
        }
        if((ch[0] == '1') && strcmp(recv_pack->data.send_user, Mex_Box[i].data.send_user) == 0 && (Mex_Box[i].type == ADD_GRP))
        {
			if(pthread_create(&pid2,NULL,deal,(void *)&Mex_Box[i]) != 0)
                my_err("pthread_create",__LINE__); 
            book++;
        }
        if((ch[0] == '1') && strcmp(recv_pack->data.send_user, Mex_Box[i].data.mes) == 0)
        {
            send_mes(fd, Mex_Box[i].type, &Mex_Box[i], "6");
            book++;
        }
        if((ch[0] == '1') && strcmp(recv_pack->data.send_user, Mex_Box[i].data.recv_user) == 0 && strcmp(Mex_Box[i].data.mes, "ok") == 0)
        {
            send_file(&Mex_Box[i]);
            book++;
        }
    }
    if(book == sign)
        sign = book = 0;
}
    

void look_fri(PACK *recv_pack)
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int flag = LOOK_FRI;
    int rows=0;
    int i;
    int fd = recv_pack->data.send_fd;

    int statu_s;
    memset(need, 0, sizeof(need));
    sprintf(need, "select *from friends where friend_user = %s", recv_pack->data.send_user);
    printf("%s\n",need);
    mysql_query(&mysql, need);
    printf("前面没问题1\n");
    
    res = mysql_store_result(&mysql);
    printf("前面没问题2\n");
    
    rows = mysql_num_rows(res);
    printf("前面没问题3\n");

    if(rows == 0)
        recv_pack->fri_info.friends_num = 0;
    else
    {
        i = 0;
        while(row = mysql_fetch_row(res))
        {
        	if(strcmp(row[0], recv_pack->data.send_user) == 0)
            {
                strcpy(recv_pack->fri_info.friends[i], row[1]);
                statu_s = row[2][0] - '0';
                recv_pack->fri_info.friends_status[i] = statu_s;
                i++;
            }   
        }
        recv_pack->fri_info.friends_num = i;
    }
    printf("前面没问题\n");
    printf("%d\n",recv_pack->fri_info.friends_num); 
    send_mes(fd, flag, recv_pack, "");
}

void get_fri_sta(PACK *recv_pack_t)
{
    PACK *recv_pack = (PACK *)recv_pack_t;
    int flag = GET_FRI_STA;
    char ch[5];
    int fd = recv_pack->data.send_fd;

    User *t = pHead;
    int flag_1 = 0;
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
        {
            flag_1 = 1;
            break;
        }
        t = t->next;
    }

    if(t->user_state == OFFLINE)
        ch[0] = '0';
    else 
        ch[0] = '1';
    ch[1] = '\0';
    
    send_mes(fd, flag, recv_pack, ch);
}

void add_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    char ch[5];
    char ss[MAX_CHAR];
    int flag = ADD_FRI;
    int fd = recv_pack->data.send_fd;

    User *t = pHead;
    int flag_2 = 0;
    Relation *q = pStart;
    int flag_3 = 0;
    Relation *pNew = (Relation *)malloc(sizeof(Relation));
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.recv_user) == 0 && strcmp(q->friend_user, recv_pack->data.send_user) == 0)
        {
            flag_3 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_3 == 1)
    {
        ch[0] = '4';
        send_mes(fd, flag, recv_pack, ch);
        free(pNew);
        pNew = NULL;
        return;
    }
    else
    {
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.recv_user) == 0)
            {
                flag_2 = 1;
                break;
            }
            t = t->next;
        }
        
        if(flag_2 == 0)
        {
            ch[0] = '3';
            send_mes(fd, flag, recv_pack, ch);
            free(pNew);
            pNew = NULL;
            return;
        }
        else
        {
            if(t->user_state != OFFLINE)
            {
                if(recv_pack->data.mes[0] == '0')
                    ch[0] = '0';
                else if(recv_pack->data.mes[0] == 'y')
                {
                    ch[0] = '1';
                    strcpy(pNew->user, recv_pack->data.recv_user);
                    strcpy(pNew->friend_user, recv_pack->data.send_user);
                    pNew->realtion = FRIEND;
                    Insert_R(pNew);
                    printf("没有问题4\n");

                    memset(need, 0, strlen(need));
                    sprintf(need, "insert into friends values('%s', '%s', %d)", recv_pack->data.recv_user, recv_pack->data.send_user, FRIEND);
                    mysql_real_query(&mysql, need, strlen(need));
                }
                else if(recv_pack->data.mes[0] == 'n')
                    ch[0] = '2';
                
                send_mes(fd, flag, recv_pack, ch);
                
            }
            else if(t->user_state == OFFLINE)
            {
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));       
            }
        }
    }
}



void del_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];
    char ch[5];
    int fd = recv_pack->data.send_fd;
    int flag = DEL_FRI;

    Relation *q = pStart;
    int flag_1 = 0;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.mes) == 0)
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 0)
        ch[0] = '0';
    else
    {
        Delete_R(q);

        memset(need, 0, strlen(need));
        sprintf(need, "delete from friends where user='%s' and friend_user='%s'", recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    send_mes(fd, flag, recv_pack, ch);
}

void shi_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];
    int flag = SHI_FRI;
    int fd = recv_pack->data.send_fd;

    char ch[5];

    Relation *q = pStart;
    int flag_1 = 0;
    while(q)
    {
        if((strcmp(q->friend_user, recv_pack->data.mes) == 0 && strcmp(q->user, recv_pack->data.send_user) == 0))
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 0)
        ch[0] = '0';
    else
    {
        q->realtion = FRI_BLK;
        memset(need, 0, strlen(need));
        sprintf(need, "update friends set realtion=%d where user='%s' and friend_user='%s'", FRI_BLK, recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    send_mes(fd, flag, recv_pack, ch);
}

void rel_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];
    int flag = REL_FRI;
    int fd = recv_pack->data.send_fd;

    char ch[5];

    Relation *q = pStart;
    int flag_1 = 0;
    while(q)
    {
        if((strcmp(q->friend_user, recv_pack->data.mes) == 0 && strcmp(q->user, recv_pack->data.send_user) == 0))
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 0)
        ch[0] = '0';
    else
    {
        q->realtion = FRI_BLK;
        memset(need, 0, strlen(need));
        sprintf(need, "update friends set realtion=%d where user='%s' and friend_user='%s'", FRI_WHI, recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    send_mes(fd, flag, recv_pack, ch);
}

void chat_one(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    int flag = CHAT_ONE;
    int fd = recv_pack->data.send_fd;
    char ch[5];
    char ss[MAX_CHAR];
    time_t now;
    char *str;
    
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1500];
    int rows;
    int fields;
    RECORD_INFO rec_info[55];
    int i = 0,j;
    
    User *t = pHead;
    Relation *q = pStart;
    Recordinfo *p = pRec;
    int flag_1 = 0;
    int flag_2 = 0;

    Recordinfo *pNew = (Recordinfo *)malloc(sizeof(Recordinfo));
    

    if(strcmp(recv_pack->data.mes, "q") == 0)
    {
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
            {
                t->user_state = ONLINE;
                t->chat[0] = '\0';
                free(pNew);
                pNew = NULL;
                return;
            }
            t = t->next;
        }
    }

    while(q)
    {
        if((strcmp(q->user,recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.recv_user) == 0) && (q->realtion == FRI_BLK))
        {
            ch[0] = '3';
            ch[1] = '\0';
            recv_pack->type = CHAT_ONE;
            memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
            strcpy(recv_pack->data.mes, "ch");
            if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                my_err("send", __LINE__);
            free(pNew);
            pNew = NULL;
            return;
        }
        q = q->next;
    }

    t = pHead;
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.recv_user) == 0)
        {
            flag_1 = 1;
            break;
        }
        t = t->next;
    }

    if(flag_1 == 0)
    {
        ch[0] = '0';
        send_mes(fd, flag, recv_pack, ch);
        free(pNew);
        pNew = NULL;
        return;
    }
    else
    {
        if(recv_pack->data.mes[0] == '1')
        {
            memset(need, 0, strlen(need));
            sprintf(need, "select * from chat_messages where send_user='%s' and recv_user='%s'", recv_pack->data.send_user, recv_pack->data.recv_user);
            mysql_real_query(&mysql, need, strlen(need));
            res = mysql_store_result(&mysql);
            rows = mysql_num_rows(res);
            fields = mysql_num_fields(res);
            while(row = mysql_fetch_row(res))
            {
                strcpy(pNew->send_user, row[0]);
                strcpy(pNew->recv_user, row[1]);
                strcpy(pNew->messages, row[2]);
                Insert_RC(pNew);
                memset(need, 0, strlen(need));
                sprintf(need, "insert into chat_messages values('%s', '%s', '%s')", row[0], row[1], row[2]);
                mysql_real_query(&mysql, need, strlen(need));
                
                strcpy(recv_pack->rec_info[i].recv_user, row[0]);
                strcpy(recv_pack->rec_info[i].send_user, row[1]);
                strcpy(recv_pack->rec_info[i].messages, row[2]);
                i++;
                if(i > 50)
                    break;                          
            }
            recv_pack->rec_info[i].messages[0] = '0';
            send_mes(fd, flag, recv_pack, "6");

            memset(need, 0, strlen(need));
            sprintf(need, "delete from chat_messages where send_user='%s' and recv_user='%s'", recv_pack->data.send_user, recv_pack->data.recv_user);
            mysql_real_query(&mysql, need, strlen(need));
            
            t = pHead;
            while(t)
            {
                if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
                {
                    t->user_state = ONE_CHAT;
                    strcpy(t->chat, recv_pack->data.recv_user);
                    break;
                }
                t = t->next;
            }
            t = pHead;
            while(t)
            {
                if(strcmp(t->nickname, recv_pack->data.recv_user) == 0 && (t->user_state != OFFLINE))
                {
                    flag_2 = 1;
                    break;
                }
                t = t->next;
            }
            if(flag_2 == 1)
            {
                ch[0] = '1';
                fd = t->fd;
                strcpy(ss,recv_pack->data.recv_user);
                strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                strcpy(recv_pack->data.send_user, ss);
                send_mes(fd, flag, recv_pack, ch);
            }
            else 
            {
                ch[0] = '2';
                send_mes(fd, flag, recv_pack, ch);
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));
            }
        }
        else
        {
            t = pHead;
            while(t)
            {
                if(strcmp(t->nickname, recv_pack->data.recv_user) == 0 && strcmp(t->chat, recv_pack->data.send_user) == 0 && (t->user_state == ONE_CHAT))
                {
                    fd = t->fd;
                    strcpy(pNew->recv_user, recv_pack->data.send_user);
                    strcpy(pNew->send_user, recv_pack->data.recv_user);
                    strcpy(pNew->messages, recv_pack->data.mes);
                    Insert_RC(pNew);

                    memset(need, 0, strlen(need));
                    sprintf(need, "insert into chat_messages values('%s', '%s', '%s')", recv_pack->data.send_user, recv_pack->data.recv_user, recv_pack->data.mes);
                    mysql_real_query(&mysql, need, strlen(need));
                    
                    memset(ss, 0, MAX_CHAR);
                    strcpy(ss,recv_pack->data.recv_user);
                    strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                    time(&now);
                    str = ctime(&now);
                    str[strlen(str) - 1] = '\0';
                    memcpy(recv_pack->data.send_user, str, strlen(str));
                  
                    send_mes(fd, flag, recv_pack, recv_pack->data.mes);
        
                    return;
                }
                else if(strcmp(t->nickname, recv_pack->data.recv_user) == 0 && strcmp(t->chat, recv_pack->data.send_user) != 0)
                {
                    memset(need, 0, strlen(need));
                    sprintf(need, "insert into off_chat_messages values('%s', '%s', '%s')", recv_pack->data.send_user, recv_pack->data.recv_user, recv_pack->data.mes);
                    mysql_real_query(&mysql, need, strlen(need));
                    free(pNew);
                    pNew = NULL;
                    return;
                }
                t = t->next;
            }
        }
    }
}

void check_mes_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    int i = 0;
    int flag = CHECK_MES_FRI;
    char ch[5];
    int fd = recv_pack->data.send_fd;
    Relation *q = pStart;
    Recordinfo *p = pRec;
    int flag_1 = 0;
    while(q)
    {
        if((strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.mes) == 0) && (q->realtion == FRIEND)) 
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }
    if(flag_1 == 0)
        ch[0] = '0';
    else
    {
        ch[0] = '1';
        while(p)
        {
            if((strcmp(p->send_user, recv_pack->data.send_user) == 0 && strcmp(p->recv_user, recv_pack->data.mes) == 0))
            {
                strcpy(recv_pack->rec_info[i].send_user, p->send_user);
                strcpy(recv_pack->rec_info[i].recv_user, p->recv_user);
                strcpy(recv_pack->rec_info[i].messages, p->messages);
                i++;
                if(i > 50)
                    break;
            }
            p = p->next;
        }
    }
    recv_pack->rec_info[i].messages[0] = '0';
                            
    send_mes(fd, flag, recv_pack, ch);
}

void cre_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    char ch[5];
    int flag = CRE_GRP;
    int fd = recv_pack->data.send_fd;

    Relation *q = pStart;
    int flag_1 = 0;
    Relation *pNew = (Relation *)malloc(sizeof(Relation));
    printf("safadssaf\n");
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.mes) == 0)
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 1)
    {
        ch[0] = '0';
    }
    
    else if(flag_1 == 0)
    {
        ch[0] = '1';
        strcpy(pNew->user, recv_pack->data.send_user);
        strcpy(pNew->friend_user, recv_pack->data.mes);
        pNew->realtion = GRP;
        Insert_R(pNew);
        
        memset(need, 0, strlen(need));

        sprintf(need, "insert into friends values('%s', '%s', %d)", recv_pack->data.send_user, recv_pack->data.mes, GRP_OWN);
        printf("%s\n",need); 
        mysql_real_query(&mysql, need, strlen(need));
        
    }
    send_mes(fd, flag, recv_pack, ch);
}

void add_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	int flag = ADD_GRP;
    int fd = recv_pack->data.send_fd;
    char need[1000];

    char ch[5];

    User *t = pHead;
    Relation *q = pStart;
    int flag_1 = 0;
    Relation *pNew = (Relation *)malloc(sizeof(Relation));
    if(strcmp(recv_pack->data.mes, "y") == 0)
    {   
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.recv_user) == 0)
            {
                fd = t->fd;
                break;
            }
            t = t->next;
        }
        ch[0] = '2';
        printf("%s\n", recv_pack->file.mes);
        strcpy(pNew->user, recv_pack->data.recv_user);
        strcpy(pNew->friend_user, recv_pack->data.send_user);
        pNew->realtion = GRP;
        Insert_R(pNew);

        memset(need, 0, strlen(need));
        sprintf(need, "insert into relationinfo values('%s', '%s', %d)", recv_pack->data.recv_user, recv_pack->data.send_user, GRP);
        mysql_real_query(&mysql, need, strlen(need));
        send_mes(fd, flag, recv_pack, ch);
        return;
    }
    else if(strcmp(recv_pack->data.mes, "n") == 0)
    {
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.recv_user) == 0)
            {
                fd = t->fd;
                break;
            }
            t = t->next;
        }
        ch[0] = '3';
        send_mes(fd, flag, recv_pack, ch);
        return;
    }
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.mes) == 0 && (q->realtion == GRP_OWN))
        {
            flag_1 = 1;
            strcpy(recv_pack->data.recv_user, q->user);
            break;
        }
        q = q->next;
    }

    if(flag_1 == 0)
    {
        ch[0] = '0';
    }
    else if(flag_1 == 1)
    {
        t = pHead;
        while(t)
        {
            if(strcmp(recv_pack->data.recv_user, t->nickname) == 0 && (t->user_state != OFFLINE))
            {
                ch[0] = '1';
                fd = t->fd;
                strcpy(recv_pack->file.mes, recv_pack->data.mes);
                break;
            }
            else if(strcmp(recv_pack->data.recv_user, t->nickname) == 0 && (t->user_state == OFFLINE))
            {
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));
                break;
            }
            t = t->next;
        }
    }
    send_mes(fd, flag, recv_pack, ch);
}

void out_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    int flag = OUT_GRP;
    char ch[5];
    int fd = recv_pack->data.send_fd;

    Relation *q = pStart;
    int flag_1 = 0;
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.mes) == 0)
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 0)
        ch[0] = '0';
    else
    {
        ch[0] = '1';
        Delete_R(q);

        memset(need, 0, strlen(need));
        sprintf(need, "delete from friends where user='%s' and friend_user='%s'", recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
    }
    send_mes(fd, flag, recv_pack, ch);
}

void del_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    int flag = DEL_GRP;
    char ch[5];
    int fd = recv_pack->data.send_fd;

    Relation *q = pStart;
    int flag_1 = 0;
    int flag_2 = 0;
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.mes) == 0)
        {
            flag_2 = 1;
            break;
        }
        q = q->next;
    }

    q = pStart;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.mes) == 0 && (q->realtion == GRP_OWN))
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_2 == 0)
        ch[0] = '0';
    else if(flag_1 == 1 && flag_2 == 1)
    {
        ch[0] = '1';
        q = pStart;
        while(q)
        {
            if(strcmp(q->friend_user, recv_pack->data.mes) == 0)
                Delete_R(q);
            q = q->next;
        }
        memset(need, 0, strlen(need));
        sprintf(need, "delete from friends where friend_user='%s'", recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
    }
    else if(flag_1 == 0 && flag_2 == 1)
        ch[0] = '2';
    send_mes(fd, flag, recv_pack, ch);
}

void set_grp_adm(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    char ch[5];
    int flag = SET_GRP_ADM;
    int fd = recv_pack->data.send_fd;
    int fd2;
    User *t = pHead;
    Relation *q = pStart;
    int flag_1 = 0;
    int flag_2 = 0;
    int flag_3 = 0;
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.recv_user) == 0)
        {
            flag_2 = 1;
            break;
        }
        q = q->next;
    }

    q = pStart;
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && strcmp(q->user, recv_pack->data.mes) == 0)
        {
            flag_3 = 1;
            break;
        }
        q = q->next;
    }

    q = pStart;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && q->realtion == GRP_OWN)
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 1 && flag_2 == 1 && flag_3 == 1)
    {
        ch[0] = '1';
        q = pStart;
        while(q)
        {
            if(strcmp(q->user, recv_pack->data.mes) == 0 && strcmp(q->friend_user, recv_pack->data.recv_user) == 0)
            {
                q->realtion = GRP_ADM;
                break;
            }
            q = q->next;
        }
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.mes) == 0 && (t->user_state != OFFLINE))
            {
                fd2 = t->fd;
                send_mes(fd2, flag, recv_pack, "6");
            }
            else if(strcmp(t->nickname, recv_pack->data.mes) == 0 && (t->user_state == OFFLINE))
            {
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));
            }
            t = t->next;
        }
        memset(need, 0, strlen(need));
        sprintf(need, "update friends set status=%d where user='%s' and friend_user='%s'", GRP_ADM, recv_pack->data.mes, recv_pack->data.recv_user);
        mysql_real_query(&mysql, need, strlen(need));
    }
    else if(flag_1 == 0 && flag_2 == 1 && flag_3 == 1)
        ch[0] = '2';
    else if(flag_3 == 0)
        ch[0] = '3';
    else if(flag_2 == 0)
        ch[0] = '0';
    send_mes(fd, flag, recv_pack, ch);
}

void kick_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    int flag = KICK_GRP;
    char ch[5];
    int fd = recv_pack->data.send_fd;
    int fd2;
    User *t = pHead;
    Relation *q = pStart;
    int flag_1 = 0;
    int flag_2 = 0;
    int flag_3 = 0;
    int flag_4 = 0;
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.recv_user) == 0)
        {
            flag_2 = 1;
            break;
        }
        q = q->next;
    }

    q = pStart;
    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && strcmp(q->user, recv_pack->data.mes) == 0)
        {
            flag_3 = 1;
            break;
        }
        q = q->next;
    }

    q = pStart;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && (q->realtion == GRP_OWN || q->realtion == GRP_ADM))
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }
    
    q = pStart;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.mes) == 0 && (q->realtion == GRP))
        {
            flag_4 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_1 == 1 && flag_2 == 1 && flag_3 == 1 && flag_4 == 1)
    {
        ch[0] = '1';
        Delete_R(q);
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.mes) == 0 && (t->user_state != OFFLINE))
            {
                fd2 = t->fd;
                send_mes(fd2, flag, recv_pack, "6");
            }
            else if(strcmp(t->nickname, recv_pack->data.mes) == 0 && (t->user_state == OFFLINE))
            {
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));
            }
            t = t->next;
        }
        memset(need, 0, strlen(need));
        sprintf(need, "delete from friends where user='%s' and friend_user='%s'", recv_pack->data.mes, recv_pack->data.recv_user);
        mysql_real_query(&mysql, need, strlen(need));
    }
    else if(flag_1 == 0 && flag_2 == 1 && flag_3 == 1 && flag_4 == 1)
        ch[0] = '2';
    else if(flag_4 == 0)
        ch[0] = '4';
    else if(flag_3 == 0)
        ch[0] = '3';
    else if(flag_2 == 0)
        ch[0] = '0';
    send_mes(fd, flag, recv_pack, ch);
}

void check_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    int flag = CHECK_GRP;
    int fd = recv_pack->data.send_fd;
    Relation *q = pStart;
    int i = 0;

    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && (q->realtion == GRP || q->realtion == GRP_OWN || q->realtion == GRP_ADM))
        {
            strcpy(recv_pack->grp_info.groups[i], q->friend_user);
            i++;
        }
        q = q->next;
    }

    recv_pack->grp_info.grp_num = i;

    send_mes(fd, flag, recv_pack, "");
}

void check_mem_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	int flag = CHECK_MEM_GRP;
    int fd = recv_pack->data.send_fd;
    Relation *q = pStart;
    int i = 0;

    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.mes) == 0 && (q->realtion == GRP || q->realtion == GRP_OWN || q->realtion == GRP_ADM))
        {
            strcpy(recv_pack->fri_info.friends[i], q->user);
            i++;
        }
        q = q->next;
    }
    recv_pack->fri_info.friends_num = i;

    send_mes(fd, flag, recv_pack, "");
}

void chat_many(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    int flag = CHAT_MANY;
    char ch[5];
    int fd = recv_pack->data.send_fd;
    char ss[MAX_CHAR];
    time_t now;
    char *str;
    
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1500];
    int rows;
    int fields;
    PACK recv_t;
    recv_t.type = flag;
    RECORD_INFO rec_info[100];
    int i = 0,j = 0;

    User *t = pHead;
    Relation *q = pStart;
    int flag_1 = 0;

    Recordinfo *pNew = (Recordinfo *)malloc(sizeof(Recordinfo));

    if(strcmp(recv_pack->data.mes, "q") == 0)
    {
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
            {
                t->user_state = ONLINE;
                free(pNew);
                pNew = NULL;
                return;
            }
            t = t->next;
        }
    }

    while(q)
    {
        if(strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && (q->realtion >= GRP))
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }
    if(flag_1 == 0)
    {
        ch[0] = '0';
        send_mes(fd, flag, recv_pack, ch);
        free(pNew);
        pNew = NULL;
        return;
    }
    else
    {
        if(strcmp(recv_pack->data.mes, "1") == 0)
        {
            memset(need, 0, strlen(need));
            sprintf(need, "select * from chat_messages where recv_user='%s'", recv_pack->data.recv_user);
            mysql_real_query(&mysql, need, strlen(need));
            res = mysql_store_result(&mysql);
            rows = mysql_num_rows(res);
            fields = mysql_num_fields(res);
            if(rows != 0)
            {
                while(row = mysql_fetch_row(res))
                {
                    if(rows <= 30)
                    {
                        strcpy(recv_pack->rec_info[i].send_user, row[0]);
                        strcpy(recv_pack->rec_info[i].recv_user, row[1]);
                        strcpy(recv_pack->rec_info[i].messages, row[2]);
                    }
                    else
                    {
                        if(rows - i <= 30)
                        {
                            strcpy(recv_pack->rec_info[j].send_user, row[0]);
                            strcpy(recv_pack->rec_info[j].recv_user, row[1]);
                            strcpy(recv_pack->rec_info[j].messages, row[2]);
                            j++;
                        }
                    }
                    i++;
                }
            }
            if(rows <= 30)
                recv_pack->rec_info[i].messages[0] = '0';
            else
                recv_pack->rec_info[j].messages[0] = '0';

            send_mes(fd, flag, recv_pack, "6");
            free(pNew);
            pNew = NULL;

            t = pHead;
            while(t)
            {
                if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
                {
                    t->user_state = MANY_CHAT;
                    strcpy(t->chat, recv_pack->data.recv_user);
                    break;
                }
                t = t->next;
            }
            q = pStart;
            while(q)
            {
                if(strcmp(q->user, recv_pack->data.send_user) != 0 && strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && (q->realtion == GRP || q->realtion == GRP_OWN || q->realtion == GRP_ADM))
                {
                    t = pHead;
                    while(t)
                    {
                        if(strcmp(q->user, t->nickname) == 0 && (t->user_state != OFFLINE))
                        {
                            ch[0] = '1';
                            fd = t->fd;
                            send_mes(fd, flag, recv_pack, ch);
                            break;
                        }
                        else if(strcmp(q->user, t->nickname) == 0 && (t->user_state == OFFLINE))
                        {
                            strcpy(recv_t.data.send_user, t->nickname);
                            strcpy(recv_t.data.recv_user, recv_pack->data.recv_user);
                            memcpy(&Mex_Box[sign++], &recv_t, sizeof(PACK));      
                            break;
                        }
                        t = t->next;
                    }
                }
                q = q->next;
            }
        }
        else
        {
            strcpy(pNew->send_user, recv_pack->data.send_user);
            strcpy(pNew->recv_user, recv_pack->data.recv_user);
            strcpy(pNew->messages, recv_pack->data.mes);
            Insert_RC(pNew);
            memset(need, 0, strlen(need));
            sprintf(need, "insert into chat_messges values('%s', '%s', '%s')", recv_pack->data.send_user, recv_pack->data.recv_user, recv_pack->data.mes);
            mysql_real_query(&mysql, need, strlen(need));

            q = pStart;
            while(q)
            {
                if(strcmp(q->friend_user, recv_pack->data.recv_user) == 0 && (q->realtion >= GRP))
                {
                    t = pHead;
                    while(t)
                    {
                        if(strcmp(q->user, t->nickname) == 0 && strcmp(t->chat, recv_pack->data.recv_user) == 0 && (t->user_state == MANY_CHAT))
                        {
                            fd = t->fd;
                            bzero(ss, MAX_CHAR);
                            strcpy(ss,recv_pack->data.recv_user);
                            strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                            time(&now);
                            str = ctime(&now);
                            str[strlen(str) - 1] = '\0';
                            memcpy(recv_pack->data.send_user, str, strlen(str));
                            send_mes(fd, flag, recv_pack, ch);
                            strcpy(recv_pack->data.send_user, ss);
                            bzero(ss, MAX_CHAR);
                            strcpy(ss,recv_pack->data.recv_user);
                            strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                            strcpy(recv_pack->data.send_user, ss);
                            break;
                        }
                        t = t->next;
                    }
                }
                q = q->next;
            }
        }
    }
}

void check_mes_grp(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	int flag = CHECK_MES_GRP;
    int i = 0;
    char ch[5];
    int fd = recv_pack->data.send_fd;
    Relation *q = pStart;
    Recordinfo *p = pRec;
    int flag_1 = 0;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.mes) == 0 && (q->realtion == GRP || q->realtion == GRP_OWN || q->realtion == GRP_ADM)) 
        {
            flag_1 = 1;
            break;
        }
        q = q->next;
    }
    if(flag_1 == 0)
        ch[0] = '0';
    else
    {
        ch[0] = '1';
        while(p)
        {
            if((strcmp(p->recv_user, recv_pack->data.mes) == 0)) 
            {
                strcpy(recv_pack->rec_info[i].send_user, p->send_user);
                strcpy(recv_pack->rec_info[i].recv_user, p->recv_user);
                strcpy(recv_pack->rec_info[i].messages, p->messages);
                i++;
                if(i > 50)
                    break;
            }
            p = p->next;
        }
    }
    recv_pack->rec_info[i].messages[0] = '0';
    
    send_mes(fd, flag, recv_pack, ch);
}

void recv_file(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    int flag = RECV_FILE;
    int fd = recv_pack->data.send_fd;
    int length = 0;
    int i = 0;
    char mes[MAX_CHAR * 3 + 1];
    char *name;
    bzero(mes, MAX_CHAR * 3 + 1);
    int fp;
    User *t = pHead;
    int flag_1 = 0;
    if(strcmp(recv_pack->data.mes,"8888") == 0)
    {
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.recv_user) == 0)
            {
                flag_1 = 1;
                break;
            }
            t = t->next;
        }
        if(flag_1 == 1)
        {
            file.file_name[file.sign_file][0] = '_';
            for(i = 0; i < strlen(recv_pack->data.send_user); i++)
            {
                if(recv_pack->data.send_user[i] == '/')
                {
                    name = strrchr(recv_pack->data.send_user, '/');
                    name++;
                    strcat(file.file_name[file.sign_file],name);
                    break;
                }
            }
            if(i == strlen(recv_pack->data.send_user))
                strcat(file.file_name[file.sign_file],recv_pack->data.send_user);

            strcpy(file.file_send_name[file.sign_file], recv_pack->data.recv_user);
            fp = creat(file.file_name[file.sign_file], S_IRWXU);
            file.sign_file++;
            close(fp);
            send_mes(fd, flag, recv_pack, "1");
        }
        else 
            send_mes(fd, flag, recv_pack, "0");
    }
    else if(strcmp(recv_pack->data.mes, "ok") == 0)
    {
        while(t)
        {
            if(strcmp(t->nickname, recv_pack->data.recv_user) == 0 && (t->user_state != OFFLINE))
            {
                flag_1 = 1;
                break;
            }
            t = t->next;
        }
        if(flag_1 == 1)
            send_file(recv_pack);
        else if(flag_1 == 0)
            memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));    
    }
    else
    {
        for(i = 0; i < file.sign_file; i++)
        {
            if(strcmp(recv_pack->data.recv_user, file.file_send_name[i]) == 0)
            {
                fp = open(file.file_name[i], O_WRONLY | O_APPEND);
                break;
            }
        }
        if(write(fp, recv_pack->file.mes, recv_pack->file.size) < 0)
            my_err("write", __LINE__);
        close(fp);
    }
}

void send_file(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    int flag = SEND_FILE;
    int fd = recv_pack->data.send_fd;
    int fd2;
    int fp;
    int length = 0;
    PACK send_file;
    send_file.type = flag;

    char ss[MAX_CHAR];
    User *t = pHead;
    int flag_1 = 0;
    int i = 0;
    pthread_mutex_lock(&mutex);
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.recv_user) == 0)
        {
            fd2 = t->fd;
            break;
        }
        t = t->next;
    }

    if(strcmp(recv_pack->data.mes, "ok") == 0)
    {
        strcpy(ss,recv_pack->data.recv_user);
        strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
        strcpy(recv_pack->data.send_user, ss);
        send_mes(fd2, flag, recv_pack, "request");
    }
    else if(recv_pack->data.mes[0] == 'y')
    {
        for(i = 0; i < file.sign_file; i++)
            if(strcmp(file.file_send_name[i], recv_pack->data.send_user) == 0)
                break;
        send_mes(fd2, flag, recv_pack, "5555");
        strcpy(recv_pack->data.recv_user, file.file_name[i]);
        send_mes(fd, flag, recv_pack, "8888");

        strcpy(send_file.data.send_user, recv_pack->data.recv_user);
        strcpy(send_file.data.recv_user, recv_pack->data.send_user);
        fp = open(file.file_name[i], O_RDONLY);
        if(fp == -1)
            printf("file: %s not find\n", file.file_name[i]);
        while((length = read(fp, send_file.file.mes, MAX_FILE - 1)) > 0)
        {
            send_file.file.size = length;
            if(send(fd, &send_file, sizeof(PACK), 0) < 0)
                my_err("send",__LINE__);
            bzero(send_file.file.mes, MAX_FILE);
        }
        printf("发送成功!\n");
        send_mes(fd, flag, recv_pack, "3333");
        send_mes(fd2, flag, recv_pack, "2222");
        remove(file.file_name[i]);
        file.file_send_name[i][0] = '\0';
        close(fp);
    }
    else if(recv_pack->data.mes[0] == 'n')
    {
        send_mes(fd2, flag, recv_pack, "1111");
        for(i = 0; i < file.sign_file; i++)
            if(strcmp(file.file_send_name[i], recv_pack->data.send_user) == 0)
                break;
        remove(file.file_name[i]);
        file.file_send_name[i][0] = '\0';
    }
    pthread_mutex_unlock(&mutex);
}

void Insert(User *pNew)
{
    User *t = pHead;
    while(t && t->next != NULL)
        t = t->next;
    t->next = pNew;
    pNew->next = NULL;
}

void Insert_RC(Recordinfo *pNew)
{
    Recordinfo *p = pRec;
    while(p && p->next != NULL)
        p = p->next;
    p->next = pNew;
    pNew->next = NULL;
}

void Insert_R(Relation *pNew)
{
    Relation *t = pStart;
    while(t && t->next != NULL)
        t = t->next;
    t->next = pNew;
    pNew->next = NULL;
}

void Delete_R(Relation *pNew)
{
    Relation *t = pStart;
    Relation *ptr;
    while(t)
    {
        if((strcmp(t->user, pNew->user) == 0 && strcmp(t->friend_user, pNew->friend_user) == 0))
        {
            if(pStart == t)
            {
                pStart = t->next;
                free(t);
                return;
            }
            ptr->next = t->next;
            free(t);
            return;
        }
        ptr = t;
        t = t->next;
    }
}


User *U_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int fields;

    User *pEnd, *pNew;

    sprintf(need, "select * from user_data");
    mysql_real_query(&mysql, need, strlen(need));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);

    while(row = mysql_fetch_row(res))
    {
        pNew = (User *)malloc(sizeof(User));
        strcpy(pNew->nickname, row[0]);
        strcpy(pNew->password, row[1]);
        pNew->user_state = OFFLINE;
        pNew->next = NULL;
        if(pHead == NULL)
            pHead = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    return pHead;
}

Relation *R_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int fields;

    Relation *pEnd, *pNew;

    sprintf(need, "select * from friends");
    mysql_real_query(&mysql, need, strlen(need));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);

    while(row = mysql_fetch_row(res))
    {
        pNew = (Relation *)malloc(sizeof(Relation));
        strcpy(pNew->user, row[0]);
        strcpy(pNew->friend_user, row[1]);
        pNew->realtion = row[2][0] - '0';
        pNew->next = NULL;
        if(pStart == NULL)
            pStart = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    return pStart;
}

Recordinfo *RC_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int fields;

    Recordinfo *pEnd, *pNew;

    sprintf(need, "select * from chat_messages");
    mysql_real_query(&mysql, need, strlen(need));
    res = mysql_store_result(&mysql);
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);

    while(row = mysql_fetch_row(res))
    {
        pNew = (Recordinfo *)malloc(sizeof(Recordinfo));
        strcpy(pNew->send_user, row[0]);
        strcpy(pNew->recv_user, row[1]);
        strcpy(pNew->messages, row[2]);
        pNew->next = NULL;
        if(pRec == NULL)
            pRec = pNew;
        else
            pEnd->next = pNew;
        pEnd = pNew;
    }
    return pRec;
}
