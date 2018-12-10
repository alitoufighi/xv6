#ifndef _TICKETLOCK_H_
#define _TICKETLOCK_H_

#include "types.h"
#include "spinlock.h"

struct ticketlock {
  // uint locked;       // Is the lock held?
  struct spinlock lk;
  int next_ticket;
  int now_serving;

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
  uint pcs[10];      // The call stack (an array of program counters)
  // that locked the lock.
} ticketlock;

void acquireticketlock(struct ticketlock*);
void releaseticketlock(struct ticketlock*);
void ticketlockinit(struct ticketlock*);
char* itoa(int val, int base);

#endif
