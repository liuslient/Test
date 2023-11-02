// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2021 Sartura
 * Based on minimal.c by Facebook */
 
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "ringbuf.h"
#include "ringbuf.skel.h"

 
static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
    if(level > LIBBPF_INFO)
        return 0;
	return vfprintf(stderr, format, args);
}

void bump_memlock_rlimit(void)
{
    struct rlimit rlim_new={ .rlim_cur=RLIM_INFINITY, .rlim_max=RLIM_INFINITY};
    if(setrlimit(RLIMIT_MEMLOCK,&rlim_new)){
        fprintf(stderr,"Failed to relimit OS source");
        exit(1);
    }
}

static volatile sig_atomic_t exiting;
static void sig_handler(int sig)
{
    exiting=true;
}

int ringbuf_event_handler(void *ctx,void *data,size_t data_sz)
{
    const struct mydata_t *md =data;
    printf("[ringbuf-handler] nr_running->%d cpu->%d\n",md->__nr_running,md->__cpu);
    return 0;
}

int main(int argc,char **argv)
{
    struct ring_buf *rb =NULL;
    struct ringbuf_bpf *skel;
    int err;

    libbpf_set_print(libbpf_print_fn);
    bump_memlock_rlimit();
    signal(SIGINT,sig_handler);
    signal(SIGTERM,sig_handler);

    skel=ringbuf_bpf__open_and_load();
    if(skel==0)
    {
        fprintf(stderr,"failed to open and verify BPF skeleton");
        return -1;
    }

    err=ringbuf_bpf__attach(skel);
    if(err)
    {
        fprintf(stderr,"Failed to BPF skeleton\n");
        goto cleanup;
    }

    rb= ring_buffer__new(bpf_map__fd(skel->maps.rb),ringbuf_event_handler,NULL,NULL);
    if(!rb){
        err=-1;
        fprintf(stderr,"Failed to create ring buffer\n");
        goto cleanup;
    }

    while(!exiting)
    {
        err=ring_buffer__poll(rb,-1);
        if(err==-EINTR){
            err=0;
            break;
        }
        if(err<0)
        {
            printf("Error polling ring buffer:%d\n",err);
            break;
        }
    }

cleanup:
    ring_buffer__free(rb);
    ringbuf_bpf__destroy(skel);
    return -err;
}