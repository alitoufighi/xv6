#include "types.h"
#include "spinlock.h"

struct ticketlock {
  // uint locked;       // Is the lock held?
  struct spinlock lk;
  int next_release_ticket;
  int next_queue_ticket;

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
  uint pcs[10];      // The call stack (an array of program counters)
  // that locked the lock.
} ticketlock;