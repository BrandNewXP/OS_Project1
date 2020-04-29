#include "headers.h"

void UnitTime()
{
	volatile unsigned long i;
	for(i = 0; i < 1000000UL; i++);
}

void SetCPU(pid_t pid, int affinity)
{
	cpu_set_t mask ;
	CPU_ZERO(&mask) ;
	CPU_SET(affinity, &mask) ;
	if(sched_setaffinity(pid, sizeof(mask), &mask) < 0)
	{
		fprintf(stderr, "sched_setaffinity failed. %s.\n", strerror(errno));
		exit(0) ;
	}
	return ;
}

void SetScheduler(pid_t pid, int priority)
{
	struct sched_param param ;
	param.sched_priority = priority ;
	if(sched_setscheduler(pid, SCHED_FIFO, &param) < 0)
	{
		fprintf(stderr, "sched_setscheduler failed. %s.\n", strerror(errno));
		exit(0) ;
	}
	return ;
}

pid_t Create(struct Process p)
{
	int pid = fork() ;
	if(pid < 0)
	{
		fprintf(stderr, "fork failed. %s.\n", strerror(errno));
		return -1 ;
	}
	if(pid == 0) //Child
	{
		for(int i = 0 ; i < p.ExecutionTime; i++)
			UnitTime() ;
		exit(0) ;
	}
	SetCPU(pid, 1) ;
	return pid ;
}