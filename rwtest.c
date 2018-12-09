#include "types.h"
// #include "rwlock.h"
#include "user.h"

int main(int argc, char* argv[])
{
	int pattern = (argc > 1) ? atoi(argv[1]) : 18;
	int priority = (argc == 3) ? atoi(argv[2]) : 0;
	rwinit();
	rwtest(pattern, priority);
	exit();
}