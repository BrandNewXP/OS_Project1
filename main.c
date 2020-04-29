#include "headers.h"

int outcomp(const void* L, const void* R) ;
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

	qsort(Queue, ProcessNum, sizeof(struct Process), outcomp) ;
	for(int i = 0 ; i < ProcessNum ; i++)
		printf("%s %d\n", Queue[i].Name, Queue[i].PID);

	return 0 ;
}

int outcomp(const void* L, const void* R) 
{
	struct Process* ptrL = (struct Process*)L ;
	struct Process* ptrR = (struct Process*)R ;
	if((ptrL -> PID) <= (ptrR -> PID))
		return -1 ;
	return 1 ;
}