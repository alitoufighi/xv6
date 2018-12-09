#ifndef _RWLOCK_
#define _RWLOCK_

char* itoa(int value, int base);

void rwlockwrite(struct tl* rw_ticket);
void rwlockread(struct tl* rw_ticket, struct tl* readers_ticket, int* read_count);
void rwlockread1(struct tl* rw_ticket);
void rwlockwrite1(struct tl* rw_ticket, struct tl* writers_ticket, int* write_count);

#endif
