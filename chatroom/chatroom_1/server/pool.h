#ifndef _POOL_H
#define _POOL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

#define MAX_THREAD_NUM 10

typedef struct work
{
    void *(* fun)(void *arg);
    void *arg;
    struct work *next;
}Work;

typedef struct
{
	
	pthread_mutex_t mutex;
    pthread_cond_t cond;

    pthread_t *pthreadid;
    Work *tasks;   
    int flag;      
    int max_thread_num;
    int task_num;  
}Pool;

Pool *pool;
void pool_init();       
int pool_add(void *(* fun)(void *arg), void *arg); 
void *thread(void *arg);   
int pool_destroy();

#endif
