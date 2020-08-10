#include"pool.h"

Pool *pool = NULL;      //全局变量
void pool_init()
{
    pool = (Pool *)malloc(sizeof(Pool));

    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->cond), NULL);

    pool->tasks = NULL;

    pool->pthreadid = (pthread_t *)malloc(sizeof(pthread_t) * MAX_THREAD_NUM);
    pool->flag = 0;
    pool->max_thread_num = MAX_THREAD_NUM;
    pool->cur_task = 0;

    int i = 0;
    for(i = 0; i < MAX_THREAD_NUM; i++)
        pthread_create(&(pool->pthreadid[i]), NULL, run, NULL);
}

int pool_add(void *(* process)(void *arg), void *arg)
{
    Work *new_work = (Work *)malloc(sizeof(Work));
    new_work->process = process;
    new_work->arg = arg;
    new_work->next = NULL;

    pthread_mutex_lock(&(pool->mutex));

    Work *temp = pool->tasks;
    if(temp)
    {
        while(temp->next)
            temp = temp->next;
        temp->next = new_work;
    }
    else
        pool->tasks = new_work;

    pool->cur_task++;

    pthread_cond_signal(&(pool->cond));
    pthread_mutex_unlock(&(pool->mutex));
    
    return 0;
}

void *run(void *arg)
{
    
    while(1)
    {
        pthread_mutex_lock(&(pool->mutex));

        while(pool->cur_task == 0 && !pool->flag)
        {
            pthread_cond_wait(&(pool->cond), &(pool->mutex));
        }
    
        if(pool->flag)
        {
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }


        pool->cur_task--;
        Work *temp = pool->tasks;
        pool->tasks = pool->tasks->next;
        pthread_mutex_unlock(&(pool->mutex));

        (*(temp->process))(temp->arg);
        free(temp);
        temp = NULL;    
    }
}

int pool_destroy()
{
    if(pool->flag)
        return -1;
    pool->flag = 1;

    pthread_cond_broadcast(&(pool->cond));
    
    int i = 0; 
    for(i = 0; i < pool->max_thread_num; i++)
        pthread_join(pool->pthreadid[i], NULL);
    free(pool->pthreadid);

    Work *temp = NULL;
    while(pool->tasks)
    {
        temp = pool->tasks;
        pool->tasks = pool->tasks->next;
        free(temp);
    }

    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->cond));

    free(pool);
    pool = NULL;
    
    return 0;
}
