#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main()
{
	int a = shm_open(1, 1, 1);
	void* x = shm_attach(1);
	int ss = shm_close(1);
	
}