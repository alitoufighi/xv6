
#include "ticketlock.h"
#include "proc.h"
#include "x86.h"
#include "defs.h"

void
acquireticketlock()
{
  pushcli();
  int ticket = fetch_and_inc(&ticketlock.next_ticket, 1);
  while(ticketlock.now_serving != ticket)
    sleepticket(&ticketlock);
  popcli();
}

void
releaseticketlock()
{
  pushcli();
  if (ticketlock.now_serving >= ticketlock.next_ticket)
    panic("release invalid ticket !");
  fetch_and_inc(&ticketlock.now_serving, 1);
  wakeup(&ticketlock); 
  popcli();
}
