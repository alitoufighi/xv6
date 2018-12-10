#ifndef _RWLOCK_
#define _RWLOCK_

#include "ticketlock.h"
#define READERS_PRIORITY 0
#define WRITERS_PRIORITY 1

char* itoa(int value, int base);

void rwlockwrite(struct ticketlock*);
void rwlockread(struct ticketlock*, struct ticketlock*, int*);

void rwlockwrite1(struct ticketlock*, struct ticketlock*, int*);
void rwlockread1(struct ticketlock*);
#endif
