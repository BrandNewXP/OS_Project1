#include "headers.h"

static int PreProcessing = -1, IsProcessing , Now, PreCSTime, cnt ;

int Next(struct Process* P, int N, char* Policy) ;
int comp(const void* L, const void* R) ;

void Schedule(struct Process* Queue, int N, char* Policy)
{
	for(int i = 0 ; i < N ; i++)
		Queue[i].PID = -1 ;

	qsort(Queue, N, sizeof(struct Process), comp) ;

	SetCPU(getpid(), 0) ;
	SetScheduler(getpid(), 99) ;

	Now = 0;
	IsProcessing = -1 ;
	cnt = 0 ;	

	while(1)
	{
		//printf("%d Working?\n", cnt);
		if(IsProcessing != -1 && Queue[IsProcessing].ExecutionTime == 0)
		{
			waitpid(Queue[IsProcessing].PID, NULL, 0) ;
			//struct timespec time ;
			//clock_gettime(CLOCK_REALTIME, &time) ;
			//Queue[IsProcessing].EndTime = time.tv_sec * 1000000000ll + time.tv_nsec ;
			Queue[IsProcessing].EndTime = syscall(MYGETTIME) ;

			char dmesg[1000] ;
			sprintf(dmesg, "[Project1] pid: %d %lld.%09lld %lld.%09lld\n", 
							Queue[IsProcessing].PID, 
							Queue[IsProcessing].StartTime / 1000000000ll, 
							Queue[IsProcessing].StartTime % 1000000000ll,
							Queue[IsProcessing].EndTime   / 1000000000ll, 
							Queue[IsProcessing].EndTime   % 1000000000ll) ;
			printf("%s", dmesg);
			//syscall(MYPRINT, dmesg) ;
			
			PreProcessing = IsProcessing ;
			IsProcessing = -1 ;
			cnt++ ;

			if(cnt == N)
				break ;
		}
		for(int i = 0 ; i < N ; i++)
			if(Queue[i].ReadyTime == Now)
			{
				Queue[i].PID = Create(Queue[i]) ;
				SetScheduler(Queue[i].PID, 1) ;
				printf("%s %d\n", Queue[i].Name, Queue[i].PID);
			}

		int NextProcess = Next(Queue, N, Policy) ;
		if(NextProcess != -1 && IsProcessing != NextProcess) //Context Switch
		{
			SetScheduler(Queue[NextProcess].PID, 99) ;
			if(Queue[NextProcess].StartTime == -1)
				Queue[NextProcess].StartTime = syscall(MYGETTIME) ;
				//struct timespec time ;
				//clock_gettime(CLOCK_REALTIME, &time) ;
				//Queue[NextProcess].StartTime = time.tv_sec * 1000000000ll + time.tv_nsec ;
					
			SetScheduler(Queue[IsProcessing].PID, 1) ;
			IsProcessing = NextProcess ;
			PreCSTime = Now ;
		}
		UnitTime() ;
		if(IsProcessing != -1)
			Queue[IsProcessing].ExecutionTime-- ;
		Now++ ;
	}
	return ;
}

int Next(struct Process* Queue, int N, char* Policy)
{
	int NextProcess = -1 ;
	if(strcmp(Policy, "FIFO") == 0)
	{
		if(IsProcessing != -1)
			return IsProcessing ;

		for(int i = 0 ; i < N ; i++)
			if(Queue[i].PID != -1 && Queue[i].ExecutionTime > 0 &&
			   (NextProcess == -1 || Queue[i].ReadyTime < Queue[NextProcess].ReadyTime))
				NextProcess = i ;
	}
	if(strcmp(Policy, "RR") == 0)
	{
		if(IsProcessing == -1)
		{
			if(PreProcessing != -1)
			{
				NextProcess = (IsProcessing + 1) % N ;

				while(Queue[NextProcess].PID == -1 || Queue[NextProcess].ExecutionTime <= 0)
					NextProcess = (NextProcess + 1) % N ;
			}
			else
				for(int i = 0 ; i < N ; i++)
					if(Queue[i].PID != -1 && Queue[i].ExecutionTime > 0)
					{
						NextProcess = i ;
						break ;
					}
		}
		else if((Now - PreCSTime) % 500 == 0)
		{
			NextProcess = (IsProcessing + 1) % N ;

			while(Queue[NextProcess].PID == -1 || Queue[NextProcess].ExecutionTime <= 0)
				NextProcess = (NextProcess + 1) % N ;
		}
		else
			NextProcess = IsProcessing ;
	}
	if(strcmp(Policy, "SJF") == 0)
	{
		if(IsProcessing != -1)
			return IsProcessing ;

		for(int i = 0 ; i < N ; i++)
			if(Queue[i].PID != -1 && Queue[i].ExecutionTime > 0 &&
			   (NextProcess == -1 || Queue[i].ExecutionTime < Queue[NextProcess].ExecutionTime))
				NextProcess = i ;
	}
	if(strcmp(Policy, "PSJF") == 0)
	{
		for(int i = 0 ; i < N ; i++)
			if(Queue[i].PID != -1 && Queue[i].ExecutionTime > 0 &&
			   (NextProcess == -1 || Queue[i].ExecutionTime < Queue[NextProcess].ExecutionTime))
				NextProcess = i ;
	}
	return NextProcess ;
}
int comp(const void* L, const void* R)
{
	struct Process* ptrL = (struct Process*)L ;
	struct Process* ptrR = (struct Process*)R ;
	if((ptrL -> ReadyTime) <= (ptrR -> ReadyTime))
		return -1 ;
	return 1 ;
}