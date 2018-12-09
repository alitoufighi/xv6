
#include "ticketlock.h"
#include "proc.h"
#include "defs.h"

void
acquireticketlock()
{
  acquire(&ticketlock.lk);
  if (ticketlock.now_serving == ticketlock.next_ticket)
  {
    ticketlock.next_ticket++;
    release(&ticketlock.lk);
    return;
  }
  
  if (myproc()->ticket == -1)
      myproc()->ticket =  ++ticketlock.next_ticket;

  while (myproc()->ticket == ticketlock.next_ticket) {
    sleepticket(myproc()->ticket, &ticketlock.lk);
  }

  release(&ticketlock.lk);
}

void
releaseticketlock()
{
  acquire(&ticketlock.lk);

  if (ticketlock.now_serving >= ticketlock.next_ticket)
    panic("release invalid ticket !");


  ticketlock.now_serving++;
  
  release(&ticketlock.lk);
}