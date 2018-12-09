
#include "ticketlock.h"
#include "proc.h"
#include "defs.h"

void
acquireticketlock()
{
  acquire(&ticketlock.lk);
  myproc()->ticket = ticketlock.next_ticket++;
  if(ticketlock.now_serving != myproc()->ticket)
    sleepticket(&ticketlock.lk);

  release(&ticketlock.lk);
}

void
releaseticketlock()
{
  acquire(&ticketlock.lk);

  if (ticketlock.now_serving >= ticketlock.next_ticket)
    panic("release invalid ticket !");

  wakeupticket(++ticketlock.now_serving); 
  release(&ticketlock.lk);
}