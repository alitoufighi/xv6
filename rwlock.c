#include "ticketlock.h"
#include "x86.h"
#include "defs.h"

char* itoa(int val, int base){
  static char buf[32] = {0};
  int i;
  for(i = 30; val && i; --i, val /= base)
    buf[i] = "0123456789abcdef"[val % base];
  return &buf[i+1];
}

// readers priority
void
rwlockwrite(struct ticketlock* rw_ticket)
{
	acquireticketlock(rw_ticket);
	cprintf("writing\n");
	releaseticketlock(rw_ticket);
}

void
rwlockread(struct ticketlock* rw_ticket, struct ticketlock* readers_ticket, int* read_count)
{
	acquireticketlock(readers_ticket);
	*read_count++;

	if (*read_count == 1)
		acquireticketlock(rw_ticket);
	
	releaseticketlock(readers_ticket);

	cprintf("reading\n");

	acquireticketlock(readers_ticket);

	*read_count--;

	if (*read_count == 0)
		releaseticketlock(rw_ticket);
	
	releaseticketlock(readers_ticket);
}

// writers priority
void
rwlockread1(struct ticketlock* rw_ticket)
{
  acquireticketlock(rw_ticket);
  cprintf("reading\n");
  releaseticketlock(rw_ticket);
}

void
rwlockwrite1(struct ticketlock* rw_ticket, struct ticketlock* writers_ticket, int* write_count)
{
  acquireticketlock(writers_ticket);
  *write_count++;

  if (*write_count == 1)
    acquireticketlock(rw_ticket);
  
  releaseticketlock(writers_ticket);

  cprintf("writing\n");

  acquireticketlock(writers_ticket);

  *write_count--;

  if (*write_count == 0)
    releaseticketlock(rw_ticket);
  
  releaseticketlock(writers_ticket);
}