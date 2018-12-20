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
			// for (long int i = 0; i < 10000; i++)
			printf(1, "Before Number is %d\n", getpid());
			// 	for (long int j = 0; j < 10000; j++);
			change_level(2);
			// for (long int i = 0; i < 10000; i++)
			// 	for (long int j = 0; j < 10000; j++);
			printf(1, "After Number is %d\n", getpid());
			break;
		}
	}
	
	// if (pid < 0)
	// {
	// 	printf(2, "fork error\n");
	// }
	
	// else if (pid == 0)
	// {
	// 	// for (long int i = 0; i < 10000; i++)
	// 	// 	for (long int j = 0; j < 10000; j++);
	// 	change_level(2);
	// 	// for (long int i = 0; i < 10000; i++)
	// 	// 	for (long int j = 0; j < 10000; j++);
	// 	printf(1, "Number is %d\n", getpid());

	// }

	if(pid > 0)
	{
		// printf(1, "waiting\n");
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished\n");
	}

	exit();
}