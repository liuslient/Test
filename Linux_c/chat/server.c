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

#define SERV_PORT 8848  
#define LISTENQ 10     
#define MAX_EVENTS 1000

#define FRIEND 1
#define FRI_BLK 2
#define FRI_WHI  3 

#define OFFLINE 0
#define ONLINE 1
		
User *U_read();                
Relation *R_read();      
void Insert_R(Relation *pNew);    
void Insert_RC(Recordinfo *pNew);  
void Delete_R(Relation *pNew);  
void DeleteLink();	
void DeleteLink_R();	
void DeleteLink_RC();


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


MYSQL mysql;
pthread_mutex_t mutex;
pthread_cond_t cond;
User *pHead = NULL;
Relation *pStart = NULL;
Recordinfo *pRec = NULL;
PACK Mex_Box[100];
int sign;
int book;

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
                ret = recv(events[i].data.fd, &pack, sizeof(PACK), MSG_WAITALL);
                pack->data.send_fd = events[i].data.fd;

                if(ret < 0)
                {
                    close(events[i].data.fd);
                    perror("revc");
                    continue;
                }
				if (recv_pack.type == EXIT)
				{
					if (send(events[i].data.fd, &recv_pack, sizeof(PACK), 0) < 0)
					{
						my_err("send", __LINE__);
					}
					memset(need, 0, sizeof(need));
                    sprintf(need, "update user_data set user_state = 0 where user_state = 1 and user_socket = %d", events[i].data.fd);
					mysql_query(&mysql, need);
					epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
				}
				if(recv_pack.type==LOGIN)
				{
					memset(need, 0, sizeof(need));
                    sprintf(need, "select *from user_data where nickname = %s", recv_pack.data.send_user);
                    mysql_query(&mysql, need);
                    result = mysql_store_result(&mysql);
                    if (!mysql_fetch_row(result))
					{
                        recv_pack.type = ACCOUNT_ERROR;
                        memset(recv_pack.data.mes, 0, sizeof(recv_pack.data.mes));
                        printf("登录错误\n");
                        strcpy(recv_pack.data.mes, "0");
                        if (send(events[i].data.fd, &recv_pack, sizeof(PACK), 0) < 0) 
						{
                            my_err("send", __LINE__);
                        }
                        continue;
                    }
 		        	memset(need, 0, sizeof(need)); 
 		        	sprintf(need, "update user_data set user_socket = %d where nickname = %s", events[i].data.fd, recv_pack.data.send_user);
 	    	    	mysql_query(&mysql, need); 
				} 
                pack= (PACK*)malloc(sizeof(PACK));
                memcpy(pack, &recv_pack, sizeof(PACK));
                pthread_create(&pid,NULL,deal,(void *)pack);
            }
        }
    }
    close(sock_fd);
    close(epfd);

    return 0;
}

User *U_read()
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query_str[1000];
    int rows;
    int fields;

    User *pEnd, *pNew;

    sprintf(query_str, "select * from user_data");
    mysql_real_query(&mysql, query_str, strlen(query_str));
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
    char query_str[1000];
    int rows;
    int fields;

    Relation *pEnd, *pNew;

    sprintf(query_str, "select * from friends");
    mysql_real_query(&mysql, query_str, strlen(query_str));
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
    char query_str[1000];
    int rows;
    int fields;

    Recordinfo *pEnd, *pNew;

    sprintf(query_str, "select * from chat_messages");
    mysql_real_query(&mysql, query_str, strlen(query_str));
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

void *deal(void *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
	switch(recv_pack->type)
	{
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
        
		dafault:
			break;
	}
}

void registe(PACK *recv_pack_t)
{
	char need[1000];
	PACK *recv_pack = (PACK *)recv_pack_t;
	
	memset(need, 0, sizeof(need));
	sprintf(need, "insert into user_data values(\"%s\",\"%s\",%d,%d)",  recv_pack->data.send_user, recv_pack->data.mes, 0, recv_pack->data.recv_fd);
	mysql_query(&mysql, need);
	memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, "1");
    if (send(recv_pack->data.recv_fd, recv_pack, sizeof(PACK), 0) < 0) 
	{
        my_err("send", __LINE__);
    }	
}

void login(PACK *recv_pack_t)
{
	char need[1000];
	PACK *recv_pack = (PACK *)recv_pack_t;
	MYSQL_RES          *result = NULL;
    MYSQL_ROW          row;
    int ret;
	
    
    
    memset(need, 0, sizeof(need));
    sprintf(need, "select *from user_data where nickname = %s", recv_pack->data.send_user);
    mysql_query(&mysql, need);
    result = mysql_store_result(&mysql);
    if (!mysql_fetch_row(result))
	{
        recv_pack->type = ACCOUNT_ERROR;
        memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
        printf("登录错误\n");
        strcpy(recv_pack->data.mes, "0");
        if (send(recv_pack->data.recv_fd, &recv_pack, sizeof(PACK), 0) < 0) 
		{
            my_err("send", __LINE__);
        }
    }
    else
	{
		recv_pack->type = REGISTE;
        memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
        strcpy(recv_pack->data.mes, "1");
        printf("登录成功\n");
        if (send(recv_pack->data.recv_fd, &recv_pack, sizeof(PACK), 0) < 0) 
		{
            my_err("send", __LINE__);
        }
	} 
}

void look_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char need[1000];
    int rows;
    int i;

    int statu_s;
    
    memset(need, 0, sizeof(need));
    sprintf(need, "select *from friends where friend_user = %s", recv_pack->data.send_user);
    mysql_query(&mysql, need);
    
    res = mysql_store_result(&mysql);
    
    rows = mysql_num_rows(res);

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
            else if(strcmp(row[1], recv_pack->data.send_user) == 0)
            {
                strcpy(recv_pack->fri_info.friends[i], row[0]);
                statu_s = row[2][0] - '0';
                recv_pack->fri_info.friends_status[i] = statu_s;
                i++;
            }   
        }
        recv_pack->fri_info.friends_num = i;
    }
    recv_pack->type = LOOK_FRI;
    memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, ""); 
    if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
        my_err("send", __LINE__);
}

void get_fri_sta(PACK *recv_pack_t)
{
    PACK *recv_pack = (PACK *)recv_pack_t;
    char ch[5];

    User *t = pHead;
    int flag = 0;
    while(t)
    {
        if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
        {
            flag = 1;
            break;
        }
        t = t->next;
    }

    if(t->user_state == OFFLINE)
        ch[0] = '0';
    else 
        ch[0] = '1';
    ch[1] = '\0';
    
    recv_pack->type = GET_FRI_STA;
    memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, "ch");
    if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
        my_err("send", __LINE__);
}


void add_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    char ch[5];
    char ss[MAX_CHAR];

    User *t = pHead;
    int flag_2 = 0;
    Relation *q = pStart;
    int flag_3 = 0;
    Relation *pNew = (Relation *)malloc(sizeof(Relation));
    while(q)
    {
        if((strcmp(q->user, recv_pack->data.recv_user) == 0 && strcmp(q->friend_user, recv_pack->data.send_user) == 0) == 0)
        {
            flag_3 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_3 == 1)
    {
        ch[0] = '4';
        ch[1] = '\0';
        recv_pack->type = ADD_FRI;
        memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
        strcpy(recv_pack->data.mes, "ch");
        if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
            my_err("send", __LINE__);
            
        
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
            ch[1] = '\0';
            
            recv_pack->type = ADD_FRI;
            memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
            strcpy(recv_pack->data.mes, "ch");
            if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                my_err("send", __LINE__);
                
            
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

                    memset(need, 0, strlen(need));
                    sprintf(need, "insert into friends values('%s', '%s', %d)", recv_pack->data.recv_user, recv_pack->data.send_user, FRIEND);
                    mysql_real_query(&mysql, need, strlen(need));
                }
                else if(recv_pack->data.mes[0] == 'n')
                    ch[0] = '2';
                
                ch[1] = '\0';
				strcpy(ss,recv_pack->data.recv_user);
                strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                strcpy(recv_pack->data.send_user, ss);
                recv_pack->type = ADD_FRI;
                memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
                strcpy(recv_pack->data.mes, "ch");
                if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                    my_err("send", __LINE__);
                
            }
            else if(t->user_state == OFFLINE)
            {
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));       
            }
        }
    }
}

void Insert_R(Relation *pNew)
{
    Relation *t = pStart;
    while(t && t->next != NULL)
        t = t->next;
    t->next = pNew;
    pNew->next = NULL;
}

void del_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];
    char ch[5];

    Relation *q = pStart;
    int flag = 0;
    while(q)
    {
        if(strcmp(q->user, recv_pack->data.send_user) == 0 && strcmp(q->friend_user, recv_pack->data.mes) == 0)
        {
            flag = 1;
            break;
        }
        q = q->next;
    }

    if(flag == 0)
        ch[0] = '0';
    else
    {
        Delete_R(q);

        memset(need, 0, strlen(need));
        sprintf(need, "delete from friends where user='%s' and friend_user='%s'", recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    ch[1] = '\0';
    recv_pack->type = DEL_FRI;
    memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, "ch");
    if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
        my_err("send", __LINE__);
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

void shi_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    int flag = SHI_FRI;
    char ch[5];
    int fd = recv_pack->data.send_fd;

    Relation *q = pStart;
    int flag_3 = 0;
    while(q)
    {
        if((strcmp(q->friend_user, recv_pack->data.mes) == 0 && strcmp(q->user, recv_pack->data.send_user) == 0))
        {
            flag_3 = 1;
            break;
        }
        q = q->next;
    }

    if(flag_3 == 0)
        ch[0] = '0';
    else
    {
        q->realtion = FRI_BLK;
        memset(need, 0, strlen(need));
        sprintf(need, "update friends set realtion=%d where user='%s' and friend_user='%s'", FRI_BLK, recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    ch[1] = '\0';
    recv_pack->type = SHI_FRI;
    memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, "ch");
    if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
        my_err("send", __LINE__);
}

void rel_fri(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];

    char ch[5];

    Relation *q = pStart;
    int flag = 0;
    while(q)
    {
        if((strcmp(q->friend_user, recv_pack->data.mes) == 0 && strcmp(q->user, recv_pack->data.send_user) == 0))
        {
            flag = 1;
            break;
        }
        q = q->next;
    }

    if(flag == 0)
        ch[0] = '0';
    else
    {
        q->realtion = FRI_BLK;
        memset(need, 0, strlen(need));
        sprintf(need, "update friends set realtion=%d where user='%s' and friend_user='%s'", FRI_WHI, recv_pack->data.send_user, recv_pack->data.mes);
        mysql_real_query(&mysql, need, strlen(need));
        ch[0] = '1';
    }
    ch[1] = '\0';
    recv_pack->type = REL_FRI;
    memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
    strcpy(recv_pack->data.mes, "ch");
    if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
        my_err("send", __LINE__);
}


void chat_one(PACK *recv_pack_t)
{
	PACK *recv_pack = (PACK *)recv_pack_t;
    char need[1000];
    
    
    
    printf("111\n");
    int flag = CHAT_ONE;
    char ch[5];
    int fd = recv_pack->data.send_fd;
    char ss[MAX_CHAR];
    time_t now;
    char *str;
    
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query_str[1500];
    int rows;
    int fields;
    RECORD_INFO rec_info[55];
    int i = 0,j;
    
    User *t = pHead;
    Relation *q = pStart;
    Recordinfo *p = pRec;
    int flag_2 = 0;
    int flag_2_2 = 0;

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
            flag_2 = 1;
            break;
        }
        t = t->next;
    }

    if(flag_2 == 0)
    {
        ch[0] = '0';
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
    else
    {
        if(recv_pack->data.mes[0] == '1')
        {
            memset(query_str, 0, strlen(query_str));
            sprintf(query_str, "select * from chat_messages where send_user='%s' and recv_user='%s'", recv_pack->data.send_user, recv_pack->data.recv_user);
            mysql_real_query(&mysql, query_str, strlen(query_str));
            res = mysql_store_result(&mysql);
            rows = mysql_num_rows(res);
            fields = mysql_num_fields(res);
            while(row = mysql_fetch_row(res))
            {
                strcpy(pNew->send_user, row[0]);
                strcpy(pNew->recv_user, row[1]);
                strcpy(pNew->messages, row[2]);
                Insert_RC(pNew);
                memset(query_str, 0, strlen(query_str));
                sprintf(query_str, "insert into chat_messages values('%s', '%s', '%s')", row[0], row[1], row[2]);
                mysql_real_query(&mysql, query_str, strlen(query_str));
                
                strcpy(recv_pack->rec_info[i].recv_user, row[0]);
                strcpy(recv_pack->rec_info[i].send_user, row[1]);
                strcpy(recv_pack->rec_info[i].messages, row[2]);
                i++;
                if(i > 50)
                    break;                          
            }
            recv_pack->rec_info[i].messages[0] = '0';
            recv_pack->type = CHAT_ONE;
            memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
            strcpy(recv_pack->data.mes, "6");
            if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                my_err("send", __LINE__);

            memset(query_str, 0, strlen(query_str));
            sprintf(query_str, "delete from chat_messages where send_user='%s' and recv_user='%s'", recv_pack->data.send_user, recv_pack->data.recv_user);
            mysql_real_query(&mysql, query_str, strlen(query_str));
            
            t = pHead;
            while(t)
            {
                if(strcmp(t->nickname, recv_pack->data.send_user) == 0)
                {
                    t->user_state = CHAT_ONE;
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
                    flag_2_2 = 1;
                    break;
                }
                t = t->next;
            }
            if(flag_2_2 == 1)
            {
                ch[0] = '1';
                fd = t->fd;
                strcpy(ss,recv_pack->data.recv_user);
                strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                strcpy(recv_pack->data.send_user, ss);
                ch[1] = '\0';
                recv_pack->type = CHAT_ONE;
                memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
                strcpy(recv_pack->data.mes, "ch");
                if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                    my_err("send", __LINE__);
            }
            else 
            {
                ch[0] = '2';
                ch[1] = '\0';
                recv_pack->type = CHAT_ONE;
                memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
                strcpy(recv_pack->data.mes, "ch");
                if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                    my_err("send", __LINE__);
                    
                memcpy(&Mex_Box[sign++], recv_pack, sizeof(PACK));
            }
        }
        else
        {
            t = pHead;
            while(t)
            {
                if(strcmp(t->nickname, recv_pack->data.recv_user) == 0 && strcmp(t->chat, recv_pack->data.send_user) == 0 && (t->user_state == CHAT_ONE))
                {
                    fd = t->fd;
                    strcpy(pNew->recv_user, recv_pack->data.send_user);
                    strcpy(pNew->send_user, recv_pack->data.recv_user);
                    strcpy(pNew->messages, recv_pack->data.mes);
                    Insert_RC(pNew);

                    memset(query_str, 0, strlen(query_str));
                    sprintf(query_str, "insert into chat_messages values('%s', '%s', '%s')", recv_pack->data.send_user, recv_pack->data.recv_user, recv_pack->data.mes);
                    mysql_real_query(&mysql, query_str, strlen(query_str));
                    
                    memset(ss, 0, MAX_CHAR);
                    strcpy(ss,recv_pack->data.recv_user);
                    strcpy(recv_pack->data.recv_user, recv_pack->data.send_user);
                    time(&now);
                    str = ctime(&now);
                    str[strlen(str) - 1] = '\0';
                    memcpy(recv_pack->data.send_user, str, strlen(str));
                  
                    ch[1] = '\0';
                    recv_pack->type = CHAT_ONE;
                    memset(recv_pack->data.mes, 0, sizeof(recv_pack->data.mes));
                    strcpy(recv_pack->data.mes, "ch");
                    if(send(recv_pack->data.send_fd, &recv_pack, sizeof(PACK), 0) < 0)
                        my_err("send", __LINE__);
        
                    return;
                }
                else if(strcmp(t->nickname, recv_pack->data.recv_user) == 0 && strcmp(t->chat, recv_pack->data.send_user) != 0)
                {
                    memset(query_str, 0, strlen(query_str));
                    sprintf(query_str, "insert into off_recordinfo values('%s', '%s', '%s')", recv_pack->data.send_user, recv_pack->data.recv_user, recv_pack->data.mes);
                    mysql_real_query(&mysql, query_str, strlen(query_str));
                    free(pNew);
                    pNew = NULL;
                    return;
                }
                t = t->next;
            }
        }
    }
}

void Insert_RC(Recordinfo *pNew)
{
    Recordinfo *p = pRec;
    while(p && p->next != NULL)
        p = p->next;
    p->next = pNew;
    pNew->next = NULL;
}
