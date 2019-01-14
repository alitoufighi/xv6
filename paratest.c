#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main()
{
	// printf(1, "open ret : %d \n", shm_open(1, 3, 0));

	// char* shared_mem = (char*)shm_attach(1);
	
	// For testing family attach permission uncomment following lines
	// if (fork() == 0)
	// {
	// 	shm_attach(1);
	// 	exit();
	// }
	// wait();

	// shared_mem[0] = 'y';
	// shared_mem[1] = '\0';
	
	double i = 0;

	for (i = 0; i < 2000000; i += 0.01)
		i = i;
	
	// printf(1, "result string : %s \n", shared_mem);

	// shm_close(1);

	exit();
}