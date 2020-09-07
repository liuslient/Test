#ifndef _CLIENT_H
#define _CLIENT_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<termios.h>
#include<assert.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define EXIT           -1
#define REGISTE         1
#define LOGIN           2
#define LOOK_FRI        3
#define GET_FRI_STA     4
#define ADD_FRI         5
#define DEL_FRI         6
#define SHI_FRI         7
#define REL_FRI         8 
#define CRE_GRP         9 
#define ADD_GRP         10 
#define OUT_GRP         11 
#define DEL_GRP         12 
#define SET_GRP         13 
#define KICK_GRP        14 
#define CHECK_GRP       15 
#define CHECK_MUM_GRP   16 
#define CHAT_FRI        17 
#define CHAT_GRP        18 
#define CHECK_MES_FRI   19 
#define CHECK_MES_GRP   20


#define MAX_CHAR 200
#define FRI_MAX 100
#define MAX_FILE 1024 

#define SERV_PORT 8017 

#define PASSIVE 0
#define ACTIVE 1

typedef struct
{
    char friends[FRI_MAX][MAX_CHAR];
    int friends_status[FRI_MAX];
    int friends_num;
}FRI_INFO;

typedef struct
{
    char groups[FRI_MAX][MAX_CHAR];
    int grp_num;
}GROUP_INFO;

typedef struct
{
    char user[MAX_CHAR];
    char other_user[MAX_CHAR];
    char message[MAX_CHAR];
}RECORD_INFO;

typedef struct
{
    int send_fd;
    int recv_fd;
    char send_name[MAX_CHAR];
    char recv_name[MAX_CHAR];    
    char mes[MAX_CHAR * 3];
}DATA;

typedef struct 
{
    int size;
    char mes[200];
}FIle;

typedef struct
{
    int type;
    DATA data;
    FIle file;
    FRI_INFO fri_info;
    GROUP_INFO grp_info;
    RECORD_INFO rec_info[100];
}PACK;

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

void *recv_back(void *arg);
int login_menu();       
int login();            
void registe();
void Menu();    
void look_fri();
void add_fri();
void del_fri();
void shi_fri();
void rel_fri();
void chat_fri();
void check_mes_fri();
void check_grp_menu();
void check_grp();
void check_mum_grp();
void cre_grp();
void add_grp();
void out_grp();
void set_grp();
void del_grp();
void kick_grp();
void chat_grp();
void check_mes_grp();
void Menu_mes_box();

void send_pack(int type, char *send_name, char *recv_name, char *mes);
int get_choice(char *choice);

int sock_fd;
char user[MAX_CHAR];
char grp_name[MAX_CHAR];
FRI_INFO fri_info;
GROUP_INFO grp_info;
RECORD_INFO rec_info[50];
char mes_file[MAX_CHAR * 3];
int shi_flag;

char name[100][MAX_CHAR];    
char mes_box[100][MAX_CHAR];
int mes_box_inc[100];
int sign;
int sign_ive[100];

pthread_mutex_t mutex;
pthread_cond_t cond;

#endif
