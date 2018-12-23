#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
	int  k, n, id;
	double x = 0,  z;

	int pid = atoi(argv[1]); //from command line
	int level = atoi(argv[2]);
	change_level(pid, level);	
	exit();
}