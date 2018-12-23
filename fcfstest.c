#include "types.h"
#include "user.h"
#define NCHILD 10

int main()
{
	int pid;
	int i, j;
	pid = getpid();

	change_level(2);

	for (i = 0; i < NCHILD; i++)
		if (pid > 0)
			pid = fork();
	
	if (pid < 0)
	{
		printf(2, "fork error\n");
	}
	
	else if (pid == 0)
	{
		for (i = 0; i < 10000; i++)
			for (j = 0; j < 10000; j++);
		change_level(2);
		for (i = 0; i < 10000; i++)
			for (j = 0; j < 10000; j++);
		printf(1, "Number is %d\n", getpid());

	}

	else
	{
		// printf(1, "waiting\n");
		for (i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished\n");
	}

	exit();
}