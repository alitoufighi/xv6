#include "types.h"
#include "user.h"
#define NCHILD 5

int main()
{
	int pid;
	int i, j;
	pid = getpid();

	// printf(1, "%d current\n", pid);
	// change_level(1);
	set_priority(2);

	for (i = 0; i < NCHILD; i++)
	{
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
			break;
		}
	}
	
	if (pid > 0)
	{
		double x = 1;
		double z;
		for ( z = 0; z < 8000000.0; z += 0.1 )
         	x =  x + 3.14 * 89.64; 
		for(i = 0; i < 10000; ++i)
			for(j = 0; j < 10000; j++); // waiting randomly before changing level
		
		pstatus();
		// set_lottery(1);

		printf(1, "Waiting for children\n");
		for (i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "User program finished\n");
	}
	
	exit();
}