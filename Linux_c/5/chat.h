#ifndef _CHAT_H
#define _CHAT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>

#define EXIT               -1
#define ACCOUNT_ERROR      -2

#define REGISTE             1
#define LOGIN               2
#define LOOK_FRI            3
#define GET_FRI_STA         4
#define ADD_FRI             5
#define DEL_FRI             6
#define SHI_FRI             7
#define REL_FRI             8
#define CHAT_ONE            9
#define CHECK_MES_FRI       10 
#define CRE_GRP             11 
#define ADD_GRP             12 
#define OUT_GRP             13 
#define DEL_GRP             14 
#define SET_GRP_ADM         15 
#define KICK_GRP            16 
#define CHECK_GRP           17 
#define CHECK_MEM_GRP       18 
#define CHAT_MANY           19
#define CHECK_MES_GRP       20
#define SEND_FILE           21
#define RECV_FILE           22

#define MAX_CHAR            200
#define FRI_MAX             300
#define BUFSIZE             1000
#define MAX_FILE             10000
#define MAX_THREAD_NUM             1000




typedef struct _user
{
    char nickname[MAX_CHAR];
    char password[MAX_CHAR];
    int user_state;
    int fd;
    char chat[MAX_CHAR];
    struct _user *next;
}User;

typedef struct _relation
{
    char user[MAX_CHAR];
    char friend_user[MAX_CHAR];
    int realtion;
    struct _relation *next;
}Relation;

typedef struct _recordinfo
{
    char send_user[MAX_CHAR];
    char recv_user[MAX_CHAR];
    char messages[BUFSIZE];
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
    char send_user[MAX_CHAR];
    char recv_user[MAX_CHAR];
    char messages[MAX_CHAR];
}RECORD_INFO;

typedef struct file
{
    int size;
    char mes[MAX_FILE];
    char file_name[MAX_THREAD_NUM][MAX_CHAR];
    char file_send_name[MAX_THREAD_NUM][MAX_CHAR];
    int sign_file;
}File;



typedef struct 
{
    int send_fd;
    int recv_fd;
    char send_user[50];
    char recv_user[50];
    char mes[MAX_CHAR];
} DATA;

typedef struct 
{
    int type;
    DATA data;
    File file;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[100];
} PACK;



void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

#endif
