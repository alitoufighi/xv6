#include "types.h"
#include "user.h"
#define NCHILD 10

// // generates a pseudo-random number using LCG between 0 and M (inclusive)
// static unsigned long X = 1; // used in pseudo-random generator
// int rand(int M) {
//   const static unsigned long a = 1103515245, c = 12345;
//   X = a * X + c; 
//   return ((unsigned int)(X / 65536) % 32768) % M + 1;
// }
/* always assuming int is at least 32 bits */
// int rand();
// int rseed = 0;
 
// inline void srand(int x)
// {
// 	rseed = x;
// }
 
// #ifndef MS_RAND
// #define RAND_MAX ((1U << 31) - 1)
 
// inline int rand()
// {
// 	return rseed = (rseed * 1103515245 + 12345) & RAND_MAX;
// }
 
// #else /* MS rand */
 
// #define RAND_MAX_32 ((1U << 31) - 1)
// #define RAND_MAX ((1U << 15) - 1)
 
// inline int rand()
// {
// 	return (rseed = (rseed * 214013 + 2531011) & RAND_MAX_32) >> 16;
// }
 
// #endif/* MS_RAND */

//////////////////////////////////////////////////////
//generates pseudo random numbers between 0 and max
//If it is desired to use this without a guarantee of uniqueness
//for a specified span of values, un-define _UNIQUE_
//
// int rand(int max)
// {
//     int min = 0;
//     int random, trying;

//     trying = 1;         
//     while(trying)
//     {
//         srand(clock());
//         random = (rand()/32767.0)*(max+1);
//         ((random >= min)
// #ifdef _UNIQUE_
//             && NotUsedRecently(random) 
// #endif
//             ) ? (trying = 0) : (trying = 1);
//     }

//     return random;
// }

// //This function is used to guarantee that a span of n generated values
// //will not be the same. To adjust the span, change the index in 
// //static int recent[n];  Note: it is required that n < (max-min)
// //otherwise an infinite loop will occur
// int NotUsedRecently (int number)
// {
//     static int recent[20];//Use No greater value for index than max - min
//     int i,j;
//     int notUsed = 1;

//     for(i=0;i<(sizeof(recent)/sizeof(recent[0]));i++)  (number != recent[i]) ? (notUsed==notUsed) : (notUsed=0, i=(sizeof(recent)/sizeof(recent[0])));
//     if(notUsed) 
//     {
//         for(j=(sizeof(recent)/sizeof(recent[0]));j>1;j--)
//         {
//             recent[j-1] = recent[j-2];
//         }
//         recent[j-1] = number;
//     }
//     return notUsed;
// }

int main()
{
    // srand(NCHILD);
	int pid;

	pid = getpid();
	set_priority(10000);

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
        printf(1, "Numbers are %d\t%d\n", random, getpid());
	}

	else
	{
		for (int i = 0; i < NCHILD; i++)
			wait();
		
		printf(1, "user program finished\n");
	}

	exit();
}