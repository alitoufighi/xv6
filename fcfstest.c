#include "types.h"
#include "user.h"
#define NCHILD 10

int main()
{
	int pid;

	pid = getpid();

	printf(1, "%d current\n", pid);
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
		for (long int i = 0; i < 1000000000; i++);
		change_level(2);
		for (long int i = 0; i < 1000000000; i++);
		printf(1, "Number is %d\n", getpid());
	}

	else
	{
		printf(1, "waiting\n");
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished\n");
		exit();
	}

	exit();
}