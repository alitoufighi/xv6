#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main()
{
	int ret = shm_open(1, 3, 0);
	printf(1, "shm_open %d\n", ret);

	char* shared_mem = (char*)shm_attach(1);
	printf(1, "shm_attach\n");

	shared_mem[0] = 'a';
	shared_mem[1] = 'a';
	shared_mem[2] = 'a';
	shared_mem[3] = '\0';

	printf(1, "parent before %s\n", shared_mem);

	if (fork() == 0)
	{
		// char* child_mem = (char*)shm_attach(1);
		shared_mem[0] = 'd';
		printf(1, "child 1 writing %c\n", shared_mem[0]);
		if (fork() == 0)
		{
			shared_mem[1] = 'p';
			printf(1, "child 2 writing %c\n", shared_mem[1]);
			exit();
		}
		wait();
		exit();
	}

	else
	{
		if (fork() == 0)
		{
			// char* child_mem = (char*)shm_attach(1);
			shared_mem[1] = 'p';
			printf(1, "child 3 writing %c\n", shared_mem[2]);
			exit();
		}
		else
		{
			double in = 0;
			for (in = 0; in < 1000000; in += 0.01)
				in = in;
			printf(1, "after %s\n", shared_mem);
			wait();
			wait();
			// shm_close(1);
			exit();
		}
	}
}