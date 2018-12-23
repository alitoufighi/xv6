#include "types.h"
#include "user.h"
#define NCHILD 10
#define PARENT_PRIORITY 1
int main()
{
	int pid;

	pid = getpid();
	set_priority(PARENT_PRIORITY);
	printf(1, "Parent - Priority: %d Pid: %d\n", PARENT_PRIORITY, getpid());
	int i;
	for (i = 0; i < NCHILD; i++)
	{
		pid = fork();
		
		if (pid < 0)
		{
			printf(2, "fork error\n");
		}

		else if (pid == 0)
		{
			int random = rand(NCHILD) + 2;
			printf(1, "Before Set Priority: Child %d\n", getpid());
			set_priority(random);
			printf(1, "After  Set Priority: Child Pid: %d\tPriority: %d\n", getpid(), random);
			break;
		}
	}

	if (pid > 0)
	{
		printf(1, "Waiting for children\n");
		for (i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "User program finished\n");
	}
	exit();
}