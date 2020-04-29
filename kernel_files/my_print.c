#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_my_print(char* string)
{
	printk("%s\n", string) ;
	return ;
}