#ifndef _HEADERS_H_
#define _HEADERS_H_

#define _GNU_SOURCE
#define MYGETTIME 334
#define MYPRINT 335

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

struct Process
{
	char Name[32] ;
	int ReadyTime ;
	int ExecutionTime ;
	pid_t PID ;
	long long int StartTime ;
	long long int EndTime ;
} ;

// Process

void UnitTime() ;
void SetCPU(pid_t pid, int affinity) ;
void SetScheduler(pid_t pid, int priority) ;
pid_t Create(struct Process p) ;

// Scheduler

void Schedule(struct Process* Queue, int N, char* Policy) ;

#endif