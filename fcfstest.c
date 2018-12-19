#include "types.h"
#include "user.h"
#define NCHILD 10

int main()
{
	int pid;

	pid = getpid();

	change_level(2);

	for (int i = 0; i < NCHILD; i++)
		if (pid > 0)
			pid = fork();
	
	if (pid < 0)
	{
		printf(2, "fork error\n");
	}
	
	else if (pid == 0)
	{
		change_level(2);
		printf(1, "Process \"%d\"s level changed to FCFS\n", getpid());
	}

	else
	{
		// printf(1, "waiting\n");
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished\n");
	}

	exit();
}