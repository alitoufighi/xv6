#include "types.h"
#include "user.h"
#define NCHILD 10

int main()
{
    // srand(NCHILD);
	int pid;

	pid = getpid();
	set_priority(10000);

	for (int i = 0; i < NCHILD; i++)
		if (pid > 0)
			pid = fork();
	
	if (pid < 0)
	{
		printf(2, "fork error\n");
	}

	else if (pid == 0)
	{
        int random = rand(NCHILD) + 2;
        // printf(1, "ANumbers are %d\t%d\n", random, getpid());
		for (long int i = 0; i < 1000000000; i++);
        set_priority(random);
		for (long int i = 0; i < 1000000000; i++);
		printf(1, "BNumbers are %d\t%d\n", random, getpid());
	}

	else
	{
		printf(2, "waiting\n");
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		// printf(1, "user program finished\n");
		exit();
	}

	// printf(2, "child pid %d finished %d \n", getpid());
	exit();
}