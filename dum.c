#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main()
{
	char* shared_mem = (char*)shm_attach(1);
		
	shared_mem[0] = 'x';

	shm_close(1);

	exit();
}