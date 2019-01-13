#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sharedm.h"
#include "syscall.h"
#include "vm.h"

#define NULL 0x0000

// static
// int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

struct shm_info* find_shm_info(int id)
{
	struct shm_info* info = NULL;
	for(int i = 0; i < SHM_COUNT; ++i)
	{
		if(shm_table.shm_information[i].id == id && shm_table.shm_information[i].used == 1)
		{
			cprintf("id : %d \n", shm_table.shm_information[i].id);
			info = &shm_table.shm_information[i];
			break;
		}
	}

	return info;
}

struct shm_info* find_unused_shm_info() {
	struct shm_info* info = NULL;
	for(int i = 0; i < SHM_COUNT; ++i) {
		info = &shm_table.shm_information[i];
		if(!(info->used))
			break;
	}
	return info;
}

int check_id(int id){
	struct shm_info* info = find_shm_info(id);
	return (int)info;
}

int has_permission(struct shm_info* info)
{
	return 1;
}

int check_flag(int flag){
	if (flag != ONLY_CHILD_CAN_ATTACH ||
		flag != ONLY_OWNER_WRITE ||
		flag != (ONLY_CHILD_CAN_ATTACH | ONLY_OWNER_WRITE)) {
		return -1;
	}
	return 0;
}

int sys_shm_open(void)
{
	int id, pgcount, flag;
	if (argint(0, &id) < 0)
		return -1;

	if (argint(1, &pgcount) < 0)
		return -1;

	if (pgcount >= MAX_PAGE_PER_SHM)
		return -1;

	if (argint(2, &flag) < 0)
		return -1;

	// if (check_flag(flag))
	// 	return -1;	

	acquire(&shm_table.lock);

	/// MUST clear
	// if (check_id(id))
	// {
	// 	release(&shm_table.lock);
	// 	return -1;
	// }


	struct shm_info* info = find_unused_shm_info();
	if(info == NULL)
	{
		release(&shm_table.lock);
		return -1;
	}

	info->owner_pid = myproc()->pid;
	info->id = id;
	info->flags = flag;
	info->refcnt = 0;
	info->size = pgcount;

	uint* frame;
	for (int i = 0; i < pgcount; ++i) {
		if((frame = (uint*)kalloc()) == 0){
			release(&shm_table.lock);
			return -1;
		}
		info->frame[i] = frame;
	}

	info->used = 1;

	release(&shm_table.lock);

	return 1;
}

int sys_shm_attach(void)
{
	int id;
	if(argint(0, &id) < 0){
		return -1;
	}

	acquire(&shm_table.lock);

	// if(!check_id(id)){
	// 	release(&shm_table.lock);
	// 	return -1;
	// }

	struct shm_info* info = find_shm_info(id);

	if (!info)
	{
		cprintf("id not found\n");
		release(&shm_table.lock);
		return -1;
	}

	if (!has_permission(info))
	{
		release(&shm_table.lock);
		return -1;
	}

	info->refcnt += 1; 
	int index;
	struct proc* curproc = myproc();
	void* return_mem = (void*)curproc->sz;

	cprintf("size of proc before %d\n", curproc->sz);

	for (index = 0; index < info->size; index++)
	{
		/// TODO: set flags

		cprintf("address %p attached iteration %d\n", *info->frame[index], index);
		if (mappages(curproc->pgdir, (void*)PGROUNDUP(curproc->sz), PGSIZE,
				*info->frame[index], PTE_W | PTE_U) < 0)
		{
			release(&shm_table.lock);
			return -1;
		}

		curproc->sz += PGSIZE;
	}
	
	cprintf("size of proc after %d\n", curproc->sz);

	release(&shm_table.lock);

	return (int)return_mem;
}

int sys_shm_close(void)
{
	int id;
	if (argint(0, &id) <0)
		return -1;
	
	// if (check_id(id))
	// 	return -1;
	
	struct proc* curproc = myproc();

	acquire(&shm_table.lock);

	struct shm_info* info = find_shm_info(id);
	
	if(info == NULL)
	{
		release(&shm_table.lock);
		return -1;
	}

	if (info->refcnt < 1)
	{
		release(&shm_table.lock);
		return -1;
	}

	info->refcnt--;

	if (info->refcnt == 0){
		for (int i = (info->size - 1); i >= 0 ; i--)
		{
			cprintf("physical mem freed %p iteration %d\n", *(info->frame[i]), i);
			kfree(info->frame[i]);
			curproc->sz -= PGSIZE;
			cprintf("free %d iteration\n", i);
		}
		info->used = 0;
	}
	
	cprintf("size of proc after close shm %d\n", curproc->sz);

	release(&shm_table.lock);

	return 1;
}