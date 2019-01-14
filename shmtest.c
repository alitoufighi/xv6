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

	shared_mem = "saeeeedddddddd";
	printf(1, "%s\n", shared_mem);

	// if (fork() == 0)
	// {
	// 	// char* child_mem = (char*)shm_attach(1);
	// 	shared_mem[0] = 'd';
	// 	printf(1, "child writing %s\n", shared_mem);
	// 	shm_close(1);
	// 	exit();
	// }

	// else
	// {
		// wait();
	shm_close(1);
	exit();
	// }
}