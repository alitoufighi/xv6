#ifndef SHAREDM_H_
#define SHAREDM_H_

#include "types.h"
#include "defs.h"
#include "spinlock.h"

#define MAX_PAGE_PER_SHM 16
#define SHM_COUNT 32

#define ONLY_OWNER_WRITE 1
#define ONLY_CHILD_CAN_ATTACH 2

struct {
	struct spinlock lock;

	struct shm_info {
		int used;	// is this being used?
		int id;
		int owner_pid;
		uint flags;
		int refcnt;
		int size;
		uint* frame[MAX_PAGE_PER_SHM];
	} shm_information[SHM_COUNT];
} shm_table;

#endif