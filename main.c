#include "headers.h"

int main(int argc, char** argv)
{
	char Policy[10] ;
	int ProcessNum ;

	scanf("%s %d", Policy, &ProcessNum) ;

	struct Process* Queue = (struct Process*)malloc(ProcessNum * sizeof(struct Process)) ;

	for(int i = 0 ; i < ProcessNum ; i++)
	{
		scanf("%s %d %d", Queue[i].Name, &Queue[i].ReadyTime, &Queue[i].ExecutionTime) ;
		Queue[i].StartTime = -1 ;
	}

	if(strcmp(Policy, "FIFO") != 0 && strcmp(Policy, "RR") != 0 &&
	   strcmp(Policy, "SJF") != 0 && strcmp(Policy, "PSJF") != 0)
	{
		fprintf(stderr, "%s\n", "Invalid policy");
		exit(0) ;
	}
	
	Schedule(Queue, ProcessNum, Policy) ;

	return 0 ;
}