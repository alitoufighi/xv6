#ifndef _RWLOCK_
#define _RWLOCK_

char* itoa(int value, int base);

void rwlockwrite(struct tl* rw_ticket);
void rwlockread(struct tl* rw_ticket, struct tl* readers_ticket, int* read_count);

#endif
