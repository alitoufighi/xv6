#include "types.h"
#include "user.h"
#define NCHILD 10

int main()
{
	int pid;

	pid = getpid();

	change_level(2);

	for (int i = 0; i < NCHILD; i++){
		if (pid > 0)
			pid = fork();

		if (pid < 0)
		{
			printf(2, "fork error\n");
		}
		
		else if (pid == 0)
		{
			int random = rand(25000);
			printf(1, "Before changing level: Process %d waiting for %d\n", getpid(), random);
			for(int i = 0; i < random * 12345; ++i); // waiting randomly before changing level
			change_level(2);
			printf(1, "After  changing level: Process %d\n", getpid());
			break;
		}
	}
	
	if(pid > 0)
	{
		printf(1, "Waiting for children\n");
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "User program finished\n");
	}

	exit();
}