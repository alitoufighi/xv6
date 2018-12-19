#include "types.h"
#include "user.h"

#define NCHILD 10

// generates a pseudo-random number using LCG between 0 and M (inclusive)
int rand(int M) {
  static unsigned long X = 1; // used in pseudo-random generator
  const static unsigned long a = 1103515245, c = 12345;
  X = a * X + c; 
  return ((unsigned int)(X / 65536) % 32768) % M + 1;
}

int main()
{
	int pid;

	pid = getpid();
	set_priority(pid);

	for (int i = 0; i < NCHILD; i++)
		if (pid > 0)
			pid = fork();
	
	if (pid < 0)
	{
		printf(2, "fork error\n");
	}

	else if (pid == 0)
	{
        int random = rand(NCHILD);
        set_priority(random);
        printf(1, "Numbers are %d %d\n", random, getpid());
	}

	else
	{
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished\n");
	}

	exit();
}