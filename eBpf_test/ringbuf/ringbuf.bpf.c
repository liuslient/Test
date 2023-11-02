// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2021 Sartura */
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include "ringbuf.h"
 
char LICENSE[] SEC("license") = "Dual BSD/GPL";

struct {
	 __uint(type,BPF_MAP_TYPE_RINGBUF);
	 __uint(max_entries,256*1024);
} rb SEC(".maps");
 
SEC("kprobe/update_rq_clock")
int update_rq_clock(struct rq *rq)
{
    struct mydata_t *mydata;
	mydata=bpf_ringbuf_reserve(&rb,sizeof(*mydata),0);
	if(mydata==0)
	{
		return 0;
	}

    mydata->__nr_running=rq->nr_running;
	mydata->__cpu=bpf_get_smp_processor_id();

	bpf_ringbuf_submit(mydata,0);	//通知用户态程序
    return 0;
}

