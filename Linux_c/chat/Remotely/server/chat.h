#ifndef _CHAT_H
#define _CHAT_H

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
#include"pool.h"

#define EXIT           -1
#define REGISTE         1
#define LOGIN           2
#define CHECK_FRI       3
#define GET_FRI_STA     4
#define ADD_FRI         5
#define DEL_FRI         6
#define SHI_FRI         7
#define REL_FRI         8 
#define CRE_GRP         9 
#define ADD_GRP         10 
#define OUT_GRP         11 
#define DEL_GRP         12 
#define SET_GRP_ADM     13 
#define KICK_GRP        14 
#define CHECK_GRP       15 
#define CHECK_MEM_GRP   16 
#define CHAT_ONE        17 
#define CHAT_MANY       18 
#define CHECK_MES_FRI   19 
#define CHECK_MES_GRP   20
#define RECV_FILE       21 
#define SEND_FILE       22 

#define FRIEND          1
#define FRI_BLK         2
#define GRP             3
#define GRP_OWN         4
#define GRP_ADM         5

#define OFFLINE         0
#define ONLINE          1
#define ONE_CHAT        2
#define MANY_CHAT       3

#define BUFSIZE         1024
#define MAX_CHAR        100
#define FRI_MAX         100
#define MAX_FILE        10000

#define SERV_PORT       8848
#define LISTENQ         10
#define MAX_EVENTS      1000

typedef struct _user
{
    char name[MAX_CHAR];
    char passwd[MAX_CHAR];
    int statu_s;
    int fd;
    char chat[MAX_CHAR];
    struct _user *next;
}User;

typedef struct _relation
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    int statu_s;
    struct _relation *next;
}Relation;

typedef struct _recordinfo
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    char message[BUFSIZE];
    struct _recordinfo *next;
}Recordinfo;

typedef struct _friends
{
    char friends[FRI_MAX][MAX_CHAR];
    int friends_status[FRI_MAX];
    int friends_num;
}FRI_INFO;

typedef struct _group
{
    char groups[FRI_MAX][MAX_CHAR];
    int grp_num;
}GROUP_INFO;

typedef struct _record
{
    char name1[MAX_CHAR];
    char name2[MAX_CHAR];
    char message[MAX_CHAR];
}RECORD_INFO;

typedef struct _data
{
    int send_fd;
    int recv_fd;
    char send_name[MAX_CHAR];
    char recv_name[MAX_CHAR];    
    char mes[MAX_CHAR * 3];
}DATA;

typedef struct file
{
    int size;
    char mes[MAX_FILE];
}FIle;

typedef struct _pack
{
    int type;
    DATA data;
    FIle file;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[55];
}PACK;

typedef struct _file
{
    char file_name[MAX_THREAD_NUM][MAX_CHAR];
    char file_send_name[MAX_THREAD_NUM][MAX_CHAR];
    int sign_file;
}File;

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

MYSQL mysql;
pthread_mutex_t mutex;
pthread_cond_t cond;
User *pHead = NULL;
Relation *pStart = NULL;
Recordinfo *pRec = NULL;

PACK Mex_Box[100];
int sign;
int sign_1;
File file;

User *User_list();     
Relation *Relation_list();         
Recordinfo *Record_list();
void Insert(User *pNew);
void Insert_RC(Recordinfo *pNew);
void Insert_R(Relation *pNew);
void Delete_R(Relation *pNew);
void Delete_User_list();	
void Delete_Relation_list();	
void Delete_Record_list();
		
void *deal(void *recv_pack_t);
void Exit(PACK *recv_pack);   
void registe(PACK *recv_pack);
void login(PACK *recv_pack);
void check_fri(PACK *recv_pack);
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
void send_mes(int fd, int flag, PACK *recv_pack, char *mes);
void send_pack(int fd, PACK *recv_pack, char *ch);

#endif
