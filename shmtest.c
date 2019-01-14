#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


// int main()
// {
// 	int ret = shm_open(1, 3, 0);
// 	printf(1, "shm_open %d\n", ret);

// 	char* shared_mem = (char*)shm_attach(1);
// 	printf(1, "shm_attach\n");

// 	shared_mem[0] = 'a';
// 	shared_mem[1] = 'a';
// 	shared_mem[2] = 'a';
// 	shared_mem[3] = 'a';
// 	shared_mem[4] = '\0';

// 	printf(1, "parent before %s\n", shared_mem);

// 	if (fork() == 0)
// 	{
// 		shared_mem[0] = 'd';
// 		printf(1, "child 1 writing %c\n", shared_mem[0]);
// 		if (fork() == 0)
// 		{
// 			shared_mem[1] = 'p';
// 			printf(1, "child 2 writing %c\n", shared_mem[1]);
// 			exit();
// 		}
// 		wait();
// 		exit();
// 	}

// 	else
// 	{
// 		if (fork() == 0)
// 		{
// 			shared_mem[2] = 'x';
// 			printf(1, "child 3 writing %c\n", shared_mem[2]);
// 			exit();
// 		}
// 		else
// 		{
// 			double in = 0;

// 			wait();
// 			wait();

// 			for (in = 0; in < 2000000; in += 0.01)
// 				in = in;
// 			printf(1, "after writing %s\n", shared_mem);
			
// 			shm_close(1);
// 			exit();
// 		}
// 	}
// }

/*********************************************************************************/

int main(int argc,char *argv[])
{
  int pid;
  int key = 2;
  int frame = 3;
  int flag = 2;
  pid = fork();
  if (pid <  0)
  {
    printf(2,"fork error\n");
    exit();
  }
  else if (pid != 0)
  {
    int addr;
    shm_open(key,frame,flag);
    while((addr = shm_attach(key)) == -1);
    *((int*)(addr+10)) = 10;
    printf(1,"address is : %d\n",addr);
    for(int i = 0; i < 20; i++){
      *((int*)(addr + 10)) = i ;
      printf(1,"value updated. new value %d\n",*((int*)(addr+10)));
      sleep(1);
    }
    //printf(1,"child adding to shared counter\n");
    printf(1,"writing finished\n");
    exit();
  }
  else{
    sleep(0);
    int addr ;
    while((addr = shm_attach(key)) == -1);
    printf(1,"address is %d\n",addr);
    for(int i =0;i<20;i++){
      printf(1,"reading value %d\n",*((int*)(addr+10)));
      sleep(1);
    }
    printf(1,"reading finished\n");
    exit();
  }
}
