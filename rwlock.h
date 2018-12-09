#ifndef _RWLOCK_
#define _RWLOCK_

char* itoa(int value, int base);

void rwlockwrite(struct ticketlock* rw_ticket);
void rwlockread(struct ticketlock* rw_ticket, struct ticketlock* readers_ticket, int* read_count);

#endif
