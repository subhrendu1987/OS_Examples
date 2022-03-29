/*Consumer.c*/
#include "common.h"

int main(){
  srand(time(NULL));
  /* open the shared memory segment */
  shm_fd = shm_open(name, O_RDWR, 0666);
  if(shm_fd<0){
  	printf("Shared memory can not be opened. Start Producer process first\n");
  	return(-1);
  }
  /* now map the shared memory segment in the address space of the process*/
  shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  printf("\nConsumer:Start\n");
  while(loop--){
  	sleepTime=rand() % max_sleep_time +1;
  	printf("\nConsumer: Sleep for %ds\n",sleepTime);
    sleep(sleepTime);
    (* shelf)--;
    printf("Consumer: Item consumed. %d Items Left\n",*shelf);
  }
  /* remove shared memory segment*/
  munmap(shelf, sizeof(int));
  close(shm_fd);
  shm_unlink(name);
  return 0;
}
