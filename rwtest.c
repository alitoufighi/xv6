#include "types.h"
#include "user.h"
#define NCHILD 10

int main(int argc, char* argv[])
{
	int pattern = (argc > 1) ? atoi(argv[1]) : 18;
	int priority = (argc == 3) ? atoi(argv[2]) : 0;

	int pid;
	rwinit();

	pid = getpid();

	for (int i = 0; i < NCHILD; i++)
		if (pid > 0)
			pid = fork();
	
	if (pid < 0)
	{
		printf(2, "fork error\n");
	}

	else if (pid == 0)
	{
		rwtest(pattern, priority);
	}

	else
	{
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished \n");
	}

	exit();
}