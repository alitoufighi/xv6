#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
	int  k, n, id;
	double x = 0,  z;

	int pid = atoi (argv[1]); //from command line
	int lottery = atoi(argv[2]);
	set_lottery(pid, lottery);	
	exit();
}