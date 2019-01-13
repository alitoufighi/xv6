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
	return 0;
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
	return 0;
}