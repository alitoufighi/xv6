#include "sharedm.h"
#include "syscall.h"

int check_id(int id){
	if(id < 0 || id >= SHM_COUNT){
		return -1;
	}
	return 0;
}

int sys_shm_open(void)
{
	int id, pgcount, flag;
	if (argint(0, &id) <0)
		return -1;
	
	if (check_id(id))
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
	int id;
	if(argint(0, &id) < 0){
		return -1;
	}

	if(check_id(id)){
		return -1;
	}

	struct shm_info info = shm_table.shm_information[id];
	info.refcnt++; 
	
	return 0x00000;
}

int sys_shm_close(void)
{
	int id;
	if (argint(0, &id) <0)
		return -1;
	
	if (check_id(id))
		return -1;
	
	acquire(&shm_table.lock);



	release(&shm_table.lock);

	return 1;
}