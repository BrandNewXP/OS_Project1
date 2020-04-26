//#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>

typedef struct Process*
{
	char Name[32] ;
	int ReadyTime ;
	int ExecutionTime ;
	pid_t PID ;
}Proc;

int main(int argc, char** argv)
{
	char Policy[10] ;
	int ProcessNum ;

	scanf("%s", Policy);
	scanf("%d", &ProcessNum) ;

	struct Proc* Queue = (Proc*)malloc(ProcessNum * sizeof(Proc)) ;

	for(int i = 0 ; i < ProcessNum ; i++)
		scanf("%s %d %d", Queue[i].name, Queue[i].ReadyTime, Queue[i].ExecutionTime) ;

	if(strcmp(Policy, "FIFO") == 0)
	else if(strcmp(Policy, "RR") == 0)
	else if(strcmp(Policy, "SJF") == 0)
	else if(strcmp(Policy, "PSJF") == 0)
	else 
	{
		fprintf(stderr, "%s\n", "Invalid policy");
		exit(0) ;
	}



	exit(0) ;
	return 0 ;
}