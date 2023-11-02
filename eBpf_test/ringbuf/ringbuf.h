#ifndef __KPROBE_H
#define __KPROBE_H

struct mydata_t{
    unsigned int __nr_running;
    int __cpu;
};

#endif