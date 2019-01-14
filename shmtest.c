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

	shared_mem[0] = 'x';
	printf(1, "shm_set\n");

	ret = shm_close(1);
	// printf(1, "%d\n", ret);

	exit();
}