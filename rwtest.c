#include "types.h"
#include "user.h"
#define NCHILD 10

char* itoa(int val, int base){
  static char buf[32] = {0};
  int i;
  for(i = 30; val && i; --i, val /= base)
    buf[i] = "0123456789abcdef"[val % base];
  return &buf[i+1];
}

int main(int argc, char* argv[])
{
	int pattern = (argc > 1) ? atoi(argv[1]) : 18;
	int priority = (argc == 3) ? atoi(argv[2]) : 0;

	char* pattern_str = itoa(pattern, 2);

	int pid;
	rwinit();

	pid = getpid();

	for (int i = 1; i < strlen(pattern_str); i++){
		if (pid > 0)
			pid = fork();

		if (pid < 0)
		{
			printf(2, "fork error\n");
		}

		else if (pid == 0)
		{
			rwtest(pattern_str[i] == '1' ? 1 : 0, priority);
		}
	}
	
	// if (pid < 0)
	// {
	// 	printf(2, "fork error\n");
	// }

	// else if (pid == 0)
	// {
	// 	rwtest(pattern, priority);
	// }

	if(pid > 0)
	{
		for (int i = 1; i < strlen(pattern_str); i++)
			wait();
		
		printf(1, "user program finished \n");
	}

	exit();
}