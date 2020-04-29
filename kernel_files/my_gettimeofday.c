#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/ktime.h>

asmlinkage long long int sys_my_gettimeofday(void)
{
	struct timespec t ;
	getnstimeofday(&t) ;
	return t.tv_sec * 1000000000ll + t.tv_nsec ;
}