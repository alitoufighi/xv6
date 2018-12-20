#include "types.h"
#include "user.h"
#define NCHILD 5

int main()
{
	int pid;

	pid = getpid();

	// printf(1, "%d current\n", pid);
	// change_level(1);
	set_priority(2);

	for (int i = 0; i < NCHILD; i++)
		if (pid > 0)
			pid = fork();
	
	if (pid < 0)
	{
		printf(2, "fork error\n");
	}
	
	else if (pid == 0)
	{
		int random = rand(NCHILD) + 1; // +1 to make it a natural number
		change_level(1);
		set_lottery(random);
		printf(1, "Lottery ticket %d set for process %d\n", random, getpid());
	}

	else
	{
		for(int i = 0; i < 10000; ++i)
			for(int j = 0; j < 10000; j++); // waiting randomly before changing level
		
		pstatus();
		// set_lottery(1);

		printf(1, "Waiting for children\n");
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "User program finished\n");
	}

	exit();
}