#include <stdio.h>
#include <pthread.h>

void thread(void)
{
  int i;
  pthread_t getid = pthread_self();
  for(i=0;i<13;i++)
  {
    printf("This is a thread printf %d,%u\n",i,getid);
    sleep(1);
  }
}

int main(void)
{
  pthread_t id;
  int i,ret;
  
  ret = pthread_create(&id,NULL,(void *) thread,NULL);
  printf("Create id %u\n",id);
  if(ret != 0)
  {
    printf("Can't create thread,error.\n");
    return 0;
  }
  for(i=0;i<13;i++)
  {
    pthread_t getid = pthread_self();
    printf("This is a main thread. %d,%u\n",i,getid);
    sleep(2);
  }
  pthread_join(id,NULL);
  return (0);
}

