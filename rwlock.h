#ifndef _RWLOCK_
#define _RWLOCK_

void rwlockwrite(struct tl* rw_ticket);
void rwlockread(struct tl* rw_ticket, struct tl* readers_ticket, int* read_count)

#endif
