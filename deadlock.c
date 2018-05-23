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

void thread1Func();
void thread2Func();
pthread_mutex_t mutA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutB = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {
  pthread_t thread1, thread2;
  if (pthread_create(&(thread1), NULL, (void *)thread1Func, NULL) != 0)
  {
      perror("pthread_create");
      exit(1);
  }
  if (pthread_create(&(thread1), NULL, (void *)thread2Func, NULL) != 0)
  {
      perror("pthread_create");
      exit(1);
  }
  if (pthread_join(thread1, NULL) != 0)
  {
      perror("pthread_join");
      exit(1);
  }
  if (pthread_join(thread2, NULL) != 0)
  {
      perror("pthread_join");
      exit(1);
  }
  return 0;
}

void thread1Func()
{
   pthread_mutex_lock(&mutA);
   printf("thread1 mutex A\n");
   
   sleep(1);
   
   pthread_mutex_lock(&mutB);
   printf("thread1 mutex B\n");
   pthread_mutex_unlock(&mutB);
   
   pthread_mutex_unlock(&mutA);
}

void thread2Func() 
{
   pthread_mutex_lock(&mutB);
   printf("thread2 mutex B\n");
   
   sleep(1);
   
   pthread_mutex_lock(&mutA);
   printf("thread2 mutex A\n");
   pthread_mutex_unlock(&mutA);
   
   pthread_mutex_unlock(&mutB);
}