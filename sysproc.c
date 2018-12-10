#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "ticketlock.h"
#include "rwlock.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_ticketlockinit(void)
{
  ticketlock.next_ticket = 0;
  ticketlock.now_serving = 0;
  return 1;
}

int counter = 0;

int
sys_ticketlocktest(void)
{
  acquireticketlock(&ticketlock);
  counter++;
  cprintf("Processing on: %d\n", counter);
  releaseticketlock(&ticketlock);
  return 0;
}

int
sys_rwinit(void)
{
  return 1;
}

int
sys_rwtest(void)
{
  struct ticketlock rw_ticket, readers_ticket, writers_ticket;
  ticketlockinit(&rw_ticket);
  ticketlockinit(&readers_ticket);
  int pattern, priority;
  // char pattern;
  int read_count = 0, write_count = 0;
  if(argint(0, &pattern) < 0)
    return -1;
  if(argint(1, &priority) < 0)
    return -1;
  
  // char* pat_str = itoa(pattern, 2);
  int i;
  // for(i = 1; i < strlen(pat_str); ++i)
  // {
  if(pattern == 0){
    if(priority == READERS_PRIORITY)
      rwlockread(&rw_ticket, &readers_ticket, &read_count);
    else
      rwlockread1(&rw_ticket);
  }
  else
  {
    if(priority == WRITERS_PRIORITY)
      rwlockwrite(&rw_ticket);
    else
      rwlockwrite1(&rw_ticket, &writers_ticket, &write_count);
  }
  // }
  return 10;
}
