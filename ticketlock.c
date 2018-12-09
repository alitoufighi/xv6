
#include "ticketlock.h"
#include "proc.h"
#include "x86.h"
#include "defs.h"

void ticketlockinit(struct tl* ticketlock)
{
  ticketlock->next_ticket = 0;
  ticketlock->now_serving = 0;
}

void
acquireticketlock(struct tl* ticketlock)
{
  pushcli();
  int ticket = fetch_and_inc(&ticketlock->next_ticket, 1);
  while(ticketlock->now_serving != ticket)
    sleepticket(ticketlock);
  popcli();
}

void
releaseticketlock(struct tl* ticketlock)
{
  pushcli();
  if (ticketlock->now_serving >= ticketlock->next_ticket)
    panic("release invalid ticket !");
  fetch_and_inc(&ticketlock->now_serving, 1);
  wakeup(ticketlock); 
  popcli();
}
