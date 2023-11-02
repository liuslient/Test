// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2021 Sartura
 * Based on minimal.c by Facebook */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "hello.skel.h"


#define PID_FILTER

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
	return vfprintf(stderr, format, args);
}

static volatile sig_atomic_t stop;

static void sig_int(int signo)
{
	stop = 1;
}

int main(int argc, char **argv)
{
	struct hello_bpf *skel;
	int err;
#ifdef PID_FILTER
    unsigned index =0;
    pid_t filter_pid=0;
    if(2!=argc){
        printf("usage:sudo ./%s filter_pid\n",argv[0]);
        return 1;
    }
    filter_pid =atoi(argv[1]);
#endif
	/* Set up libbpf errors and debug info callback */
    libbpf_set_strict_mode(LIBBPF_STRICT_ALL);
	libbpf_set_print(libbpf_print_fn);

	/* Open load and verify BPF application */
	skel = hello_bpf__open_and_load();
	if (!skel) {
		fprintf(stderr, "Failed to open BPF skeleton\n");
		return 1;
	}

#ifdef PID_FILTER
    //把map数组中下标为0的元素更新为filter_pid，filter_pid就是用户指定的pid
    err=bpf_map__update_elem(skel->maps.my_pid_map,&index,sizeof(index),&filter_pid,sizeof(pid_t),BPF_ANY);

    if(err<0)
    {
        fprintf(stderr,"Error updating map with pid : %s\n",strerror(err));
        return 1;
    }
#endif

	/* Attach tracepoint handler */
	err = hello_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n");
		goto cleanup;
	}

	if (signal(SIGINT, sig_int) == SIG_ERR) {
		fprintf(stderr, "can't set signal handler: %s\n", strerror(errno));
		goto cleanup;
	}

    fprintf(stderr,"成功\n");
	while (!stop) {
		fprintf(stderr, ".");
		sleep(1);
	}

cleanup:
	hello_bpf__destroy(skel);
	return -err;
}
