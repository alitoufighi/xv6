#include "types.h"
#include "user.h"
#define L1NCHILD 80
#define L2NCHILD 80
#define L3NCHILD 10

#define PARENT_PRIORITY 1

// int main()
// {
// 	int pid;
// 	double i, j, k;
// 	int num_of_childs = 0;
// 	pid = getpid();

// 	change_level(3);
// 	set_priority(1000);

// 	for (i = 0; i < L3NCHILD; i++)
// 	{
// 		if (pid > 0){
// 			printf(1, "%d ", ++num_of_childs);
// 			pid = fork();
// 		}
		
// 		if (pid < 0)
// 		{
// 			printf(2, "fork error\n");
// 		}

// 		else if (pid == 0)
// 		{
// 			int random = rand(L3NCHILD) + 2;
// 			// printf(1, "Before Set Priority: Child %d\n", getpid());
// 			set_priority(random);
// 			// printf(1, "After  Set Priority: Child Pid: %d\tPriority: %d\n", getpid(), random);
// 			break;
// 		}
// 	}
	
// 	if (pid > 0)
// 	{
// 		for (i = 0; i < L2NCHILD; i++){
// 			if (pid > 0){
// 				printf(1, "%d ", ++num_of_childs);
// 				pid = fork();
// 			}
// 			double x = 1;
// 			for(i = 0; i < 0xFFFF; i+=0.001)
// 				x *= 434324;

// 			if (pid < 0)
// 			{
// 				printf(2, "fork error\n");
// 			}
			
// 			else if (pid == 0)
// 			{
// 				int random = rand(25000);
// 				// printf(1, "Before changing level: Process %d waiting for %d\n", getpid(), random);
// 				for(i = 0; i < random * 12345; ++i); // waiting randomly before changing level
// 				change_level(2);
// 				// printf(1, "After  changing level: Process %d\n", getpid());
// 				break;
// 			}
// 		}

// 		if (pid > 0)
// 		{
// 			for (i = 0; i < L1NCHILD; i++)
// 			{
// 				if (pid > 0){
// 					printf(1, "%d ", ++num_of_childs);
// 					pid = fork();
// 				}
// 				double x = 1;
// 				// for(i = 0; i < 0xFFFFF; i+=0.1)
// 				// 		for(k = 0; k < 0xFFFFF; k+=0.1)
// 				// 			for(j = 0; j < 0xFFFFF; j+=0.1)
// 				// 				x *= i * j * 434324;
// 				for(i = 0; i < 0xFFFF; i+=0.001)
// 					x *= 434324;

// 				if (pid < 0)
// 				{
// 					printf(2, "fork error\n");
// 				}
				
// 				else if (pid == 0)
// 				{
// 					int random = rand(L1NCHILD) + 1; // +1 to make it a natural number
// 					change_level(1);
// 					set_lottery(random);
// 					// printf(1, "Lottery ticket %d set for process %d\n", random, getpid());
// 					break;
// 				}
// 			}

// 			if (pid > 0)
// 			{
// 				change_level(3);
// 				set_priority(100);
// 				double x = 1;
				// for(i = 0; i < 0xFFFF; i+=0.001)
				// 	x *= 434324;
// 				// for(i = 0; i < 0xFFFFF; i+=0.1)
// 				// 		for(k = 0; k < 0xFFFFF; k+=0.1)
// 				// 			for(j = 0; j < 0xFFFFF; j+=0.1)
// 				// 				x *= i * j * 434324;
// 				// pstatus();
 
// 				printf(1, "\n\n");
// 				for (i = 0; i <= (L1NCHILD + L2NCHILD + L3NCHILD); i++){
// 					wait();
// 					printf(1, "%d ", --num_of_childs);	
// 				}
				
// 				printf(1, "\nUser program finished\n");
// 			}
// 		}
// 	}
// 	exit();
// }

int main(){
	int i, j, k;
	int pid = getpid();
	int num_of_childs=0;
	for (i = 0; i < L3NCHILD; i++)
	{
		if (pid > 0){
			printf(1, "%d ", ++num_of_childs);
			pid = fork();
		}
		
		if (pid < 0)
		{
			printf(2, "fork error\n");
		}

		if (pid == 0)
		{
			double x = 1;
			for(j = 0; j < 0xFF; j+=0.1)
				x *= 434324;
			int random = rand(L3NCHILD) + 2;
			// printf(1, "Before Set Priority: Child %d\n", getpid());
			// set_priority(random);
			printf(1, "\nChild Finished.\n");
			break;
		}
	}
	if(pid > 0){
		printf(1, "\n\n");
		for(k = 0; k < L3NCHILD; ++k){
			wait();
			printf(1, "%d ", num_of_childs--);
		}
		printf(1, "\nParent Finished.\n");
	}
	exit();
}