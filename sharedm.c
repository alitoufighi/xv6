#include "sharedm.h"
#include "syscall.h"

int sys_shm_open(void)
{
	int id, pgcount, flag;
	if (argint(0, &id) <0)
		return -1;
	
	if (argint(1, &pgcount) <0)
		return -1;

	if (argint(2, &flag) < 0)
		return -1;

	acquire(&shm_table.lock);



	release(&shm_table.lock);

	return 1;
}

int sys_shm_attach(void)
{
	return 0x00000;
}

int sys_shm_close(void)
{
	int id;
	if (argint(0, &id) <0)
		return -1;
	
	acquire(&shm_table.lock);



	release(&shm_table.lock);

	return 1;
}