#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "memlayout.h"
#include "proc.h"
#include "sharedm.h"
#include "syscall.h"
#include "vm.h"

#define NULL 0x0000

int has_attach_permission(struct shm_info* info, struct proc* p)
{
	if (!((info->flags >> 1) & 0x1))
		return 1;

	struct proc* parent_proc = p->parent;
	while(parent_proc->pid != 1)
	{
		if (parent_proc->pid == info->owner_pid)
			return 1;

		parent_proc = parent_proc->parent;
	}

	return 0;
}

int check_valid_flag(int flag){
	if (flag != ONLY_CHILD_CAN_ATTACH &&
		flag != ONLY_OWNER_WRITE &&
		flag != (ONLY_CHILD_CAN_ATTACH | ONLY_OWNER_WRITE) &&
		flag != 0) 
	{
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

	// cprintf("pgcount : %d \n", pgcount);
	if (pgcount >= MAX_PAGE_PER_SHM)
		return -1;

	if (argint(2, &flag) < 0)
		return -1;

	if (check_valid_flag(flag))
		return -1;	

	acquire(&shm_table.lock);
	struct shm_info* info = NULL;
	for (int i = 0; i < SHM_COUNT; i++)
	{
		if (shm_table.shm_information[i].used == 0)
		{
			info = &(shm_table.shm_information[i]);
			break;
		}
	}

	if(info == NULL)
	{
		release(&shm_table.lock);
		return -1;
	}
	info->owner_pid = myproc()->pid;
	info->id = id;
	// cprintf("id : %d, pid : %d\n", info->id, info->owner_pid);
	info->flags = flag;
	info->refcnt = 0;
	info->size = pgcount;
	uint* frame;
	for (int i = 0; i < pgcount; ++i) {
		if((frame = (uint*)kalloc()) == 0){
			release(&shm_table.lock);
			return -1;
		}

		// cprintf("address %p opened iteration %d\n", frame, i);
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

	struct shm_info* info = NULL;
	
	for (int i = 0; i < SHM_COUNT; i++)
	{
		if (shm_table.shm_information[i].id == id)
		{
			// cprintf("id found \n");
			info = &(shm_table.shm_information[i]);
			break;
		}
	}

	if (!info)
	{
		// cprintf("id not found\n");
		release(&shm_table.lock);
		return -1;
	}

	struct proc* curproc = myproc();


	if (!has_attach_permission(info, curproc))
	{
		// cprintf("no permission to attach\n");
		release(&shm_table.lock);
		return -1;
	}

	info->refcnt += 1; 
	int index;
	void* return_mem = (void*)curproc->sz;

	// cprintf("size of proc %d before %d\n", curproc->pid, curproc->sz);

	// cprintf("owner pid : %d \n", info->owner_pid);
	// cprintf("attaching size : %d \n", info->size);

	for (index = 0; index < info->size; index++)
	{
		// cprintf("address %p attached iteration %d\n", info->frame[index], index);
		if (info->flags % 2 == 0)
		{
			if (mappages(curproc->pgdir, PGROUNDUP(curproc->sz), PGSIZE, V2P(info->frame[index]), PTE_W | PTE_U) < 0)
			{
				release(&shm_table.lock);
				return -1;
			}
		}
		else 
		{
			if (mappages(curproc->pgdir, PGROUNDUP(curproc->sz), PGSIZE, V2P(info->frame[index]), PTE_U) < 0)
			{
				release(&shm_table.lock);
				return -1;
			}
		}

		curproc->sz += PGSIZE;
	}

	curproc->shmem_data[curproc->num_of_shmem].shmem_id = info->id;
	curproc->shmem_data[curproc->num_of_shmem].start_va = curproc->sz - info->size * PGSIZE;
	curproc->num_of_shmem++;

	// cprintf("size of proc %d after %d\n", curproc->pid, curproc->sz);

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

	struct shm_info* info = NULL;
	
	for (int i = 0; i < SHM_COUNT; i++)
	{
		if (shm_table.shm_information[i].id == id)
		{
			// cprintf("id found \n");
			info = &(shm_table.shm_information[i]);
			break;
		}
	}

	info->refcnt--;

	if (info->refcnt == 0)
	{
		for (int i = (info->size - 1); i >= 0 ; i--)
		{
			uint pa;
			// cprintf("physical mem freed %p iteration %d\n", (char*)(info->frame[i]), i);
			curproc->sz -= PGSIZE;
			uint* pte = walkpgdir(curproc->pgdir, (char*)curproc->sz, 0);
			pa = PTE_ADDR(*pte);
			char *v = P2V(pa);
			kfree(v);
			*pte = 0;
			// cprintf("free %d iteration\n", i);
		}
		info->used = 0;
	}
	
	else 
	{
		// cprintf("only size is decreasing\n");
		curproc->sz -= info->size * PGSIZE;
		uint* pte = walkpgdir(curproc->pgdir, (char*)curproc->sz, 0);
		uint pa;
		pa = PTE_ADDR(*pte);
		char *v = P2V(pa);
		*pte = 0;
	}

	// cprintf("size of proc %d after close shm %d\n", curproc->pid, curproc->sz);

	release(&shm_table.lock);

	return 1;
}