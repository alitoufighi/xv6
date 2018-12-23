#include "types.h"
#include "user.h"
#define L1NCHILD 80
#define L2NCHILD 80
#define L3NCHILD 80

#define PARENT_PRIORITY 1

int main()
{
	int pid;
	int i, j;
	pid = getpid();

	change_level(3);
	set_priority(1000);

	for (i = 0; i < L3NCHILD; i++)
	{
		pid = fork();
		
		if (pid < 0)
		{
			printf(2, "fork error\n");
		}

		else if (pid == 0)
		{
			int random = rand(L3NCHILD) + 2;
			printf(1, "Before Set Priority: Child %d\n", getpid());
			set_priority(random);
			printf(1, "After  Set Priority: Child Pid: %d\tPriority: %d\n", getpid(), random);
			break;
		}
	}
	
	if (pid > 0)
	{
		for (i = 0; i < L2NCHILD; i++){
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
				for(i = 0; i < random * 12345; ++i); // waiting randomly before changing level
				change_level(2);
				printf(1, "After  changing level: Process %d\n", getpid());
				break;
			}
		}

		if (pid > 0)
		{
			for (i = 0; i < L1NCHILD; i++)
			{
				pid = fork();
			
				if (pid < 0)
				{
					printf(2, "fork error\n");
				}
				
				else if (pid == 0)
				{
					int random = rand(L1NCHILD) + 1; // +1 to make it a natural number
					change_level(1);
					set_lottery(random);
					printf(1, "Lottery ticket %d set for process %d\n", random, getpid());
					break;
				}
			}

			if (pid > 0)
			{
				for(i = 0; i < 10000; ++i)
					for(j = 0; j < 10000; j++); // waiting randomly before changing level
				
				change_level(3);
				set_priority(100);

				pstatus();
 
				printf(1, "Waiting for children\n");
				for (i = 0; i < (L1NCHILD + L2NCHILD + L3NCHILD); i++)
					wait();
				
				printf(1, "User program finished\n");
			}
		}
	}
	exit();
}
