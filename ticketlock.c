#include "proc.h"
#include "ticketlock.h"
#include "defs.h"

void
acquireticketlock()
{
  acquire(&ticketlock.lk);
  if (ticketlock.next_queue_ticket == ticketlock.next_release_ticket)
    return;
  
  if (myproc()->ticket == -1)
      myproc()->ticket =  ++ticketlock.next_queue_ticket;

  while (myproc()->ticket == ticketlock.next_release_ticket) {
    // sleepticket(ticketlock, myproc()->ticket);
  }

  release(&ticketlock.lk);
}

// releaseticketlock()
// {

// }