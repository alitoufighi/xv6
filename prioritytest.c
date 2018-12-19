#include "types.h"
#include "user.h"
#define NCHILD 10
#define PARENT_PRIORITY 10000
int main()
{
	int pid;

	pid = getpid();
	set_priority(PARENT_PRIORITY);

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
        set_priority(random);
		printf(1, "Child  - Priority: %d\t Pid: %d\n", random, getpid());
	}

	else
	{
        printf(1, "Parent - Priority: %d Pid: %d\n", PARENT_PRIORITY, getpid());
		for (int i = 0; i < NCHILD; i++)
			wait();   
	}
	exit();
}