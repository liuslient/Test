#include "vmlinux.h" //需要内核支持BTF
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

// 现在的eBPF程序，不管什么进程打开文件，都会打印文件名称出来，
// 如果只打印用户指定进程ID打开的文件名称，要怎么做？
//   用户态程序通过map，把指定的进程ID传给内核态的eBPF程序
//   如果调用 do_sys_open 接口的当前进程ID不等于用户指定的进程ID，就不输出打印，否则打印；

// 定义1个数组类型的map,数组长度为1，key 为数组下标，value是用户指定的PID(进程ID)
struct {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__uint(max_entries, 1);
	__type(key, u32);       // array数组下标
	__type(value, pid_t);   // 用户指定的pid
} my_pid_map SEC(".maps");

char LICENSE[] SEC("license") = "Dual BSD/GPL";

SEC("kprobe/do_sys_open")
int BPF_KPROBE(do_sys_open, int dfd, const char *filename)
{
	u32 index = 0;
    
    // 获取调用 do_sys_open 内核接口的当前进程ID
	pid_t pid = bpf_get_current_pid_tgid() >> 32;
    
    // 查找数组下标为0的数组元素值，即应用层传下来的 PID
	pid_t *my_pid = bpf_map_lookup_elem(&my_pid_map, &index);

    // 如果当前进程ID不等于应用层指定的PID，就不打印
	if (!my_pid || *my_pid != pid)
		return 1;

	bpf_printk("do_sys_open: name=%s\n", filename);

	return 0;
}