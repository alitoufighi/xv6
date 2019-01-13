#include "sharedm.h"
#include "proc.h"
#include "syscall.h"

struct shm_info* find_shm_info(int id){
	acquire(&shm_table.lock);
	struct shm_info* info = 0x0000;
	for(int i = 0; i < SHM_COUNT; ++i){
		*info = shm_table.shm_information[i];
		if(info->id == id)
			break;
	}
	release(&shm_table.lock);

	return info;
}

int check_id(int id){
	struct shm_info* info = find_shm_info(id);
	return (int)info;
}

int check_flag(int flag){
	if (flag != ONLY_CHILD_CAN_ATTACH ||
		flag != ONLY_OWNER_WRITE ||
		flag != ONLY_CHILD_CAN_ATTACH | ONLY_OWNER_WRITE) {
		return -1;
	}
	return 0;
}

int sys_shm_open(void)
{
	int id, pgcount, flag;
	if (argint(0, &id) < 0)
		return -1;
	
	if (check_id(id))
		return -1;

	if (argint(1, &pgcount) < 0)
		return -1;
	
	if (pgcount >= MAX_PAGE_PER_SHM)
		return -1;

	if (argint(2, &flag) < 0)
		return -1;

	if (check_flag(flag))
		return -1;
	

	acquire(&shm_table.lock);

	struct shm_info info = shm_table.shm_information[id];
	info.owner_pid = myproc()->pid;
	info.flags = flag;
	info.refcnt = 0;
	info.size = pgcount;
	uint* frame;
	for (int i = 0; i < pgcount; ++i) {
		if((frame = kalloc()) == 0){
			return -1;
		}
		info.frame[i] = frame;
	}

	release(&shm_table.lock);

	return 1;
}

int sys_shm_attach(void)
{
	int id;
	if(argint(0, &id) < 0){
		return -1;
	}

	if(!check_id(id)){
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