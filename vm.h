#ifndef VM_H_
#define VM_H_

#include "param.h"
#include "types.h"
#include "defs.h"

int
mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

#endif