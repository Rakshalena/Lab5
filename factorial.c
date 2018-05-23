#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

struct FactorialStruct
{
    int result;
    int counter;
    int k;
    int mod;
};

void parallelFactorial(void *);
void printResult(int result);
int result = 0; /* A shared result for any threads */
int counter = 0; /* A shared counter for any threads */
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {
  struct FactorialStruct factorialStruct;
  factorialStruct.result = 1;
  factorialStruct.counter = 1;
  factorialStruct.k = 0;
  factorialStruct.mod = 0;
  int tnum = 0;
  while (true) 
  {
		int current_optind = optind ? optind : 1;

		static struct option options[] = { { "k", required_argument, 0, 0 },
		{ "mod", required_argument, 0, 0 },
		{ "tnum", required_argument, 0, 0 },
		{ 0, 0, 0, 0 } };

		int option_index = 0;
		int c = getopt_long(argc, argv, "f", options, &option_index);

		if (c == -1) break;

		switch (c) {
		case 0:
			switch (option_index) {
			case 0:
				factorialStruct.k = atoi(optarg);
				printf("k = %d\n", factorialStruct.k);
				break;
			case 1:
				factorialStruct.mod = atoi(optarg);
				printf("mod = %d\n", factorialStruct.mod);
				break;
			case 2:
				tnum = atoi(optarg);
				printf("number of threads = %d\n", tnum);
				break;
			defalut:
				printf("Index %d is out of options\n", option_index);
			}
			break;
		case '?':
			break;

		default:
			printf("getopt returned character code 0%o?\n", c);
		}
  }
  pthread_t thread[tnum];
  for(int i = 0; i<tnum; i++)
  {
        if (pthread_create(&(thread[i]), NULL, (void *)parallelFactorial, (void *)&factorialStruct) != 0) 
        {
            perror("pthread_create");
            exit(1);
        }
  }
  for(int i = 0; i<tnum; i++)
  {
      if (pthread_join(thread[i], NULL) != 0) 
      {
            perror("pthread_join");
            exit(1);
      }
  }

  printResult(factorialStruct.result);

  return 0;
}

void parallelFactorial(void* args)
{
  struct FactorialStruct* f = (struct FactorialStruct*) args;
  while((f->counter) <= (f->k))
  {
    pthread_mutex_lock(&mut);
    f->result = (f->result*f->counter)%f->mod;
    f->counter++;
	pthread_mutex_unlock(&mut);
	for(volatile int i = 0; i<5000; i++)
	{
	    
	}
  }
}

void printResult(int result) {
  printf("\nAll done, k! = %d\n", result);
}