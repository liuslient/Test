#ifndef _CHAT_H
#define _CHAT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>

#define EXIT               -1
#define REGISTE             1
#define LOGIN               2
#define ACCOUNT_ERROR      -2
#define LOOK_FRI            3
#define GET_FRI_STA         4
#define ADD_FRI             5
#define DEL_FRI             6
#define SHI_FRI             7
#define REL_FRI             8
#define CHAT_ONE            9

#define MAX_CHAR            200
#define FRI_MAX             300
#define BUFSIZE             1000




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


typedef struct {
    int               send_fd;
    int               recv_fd;
    char              send_user[50];
    char              recv_user[50];
    char              mes[MAX_CHAR];
} DATA;

typedef struct {
    int               type;
    DATA              data;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[55];
} PACK;



void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

#endif
