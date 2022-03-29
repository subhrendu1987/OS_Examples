/*Producer.c*/
#include "common.h"

int main(){
  srand(time(NULL));
  /* make * shelf shared between processes*/
  //create the shared memory segment
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  //configure the size of the shared memory segment
  ftruncate(shm_fd,sizeof(int));
  //map the shared memory segment in process address space
  shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd, 0);
  printf("\nProducer:Start\n");
  while(loop--){
  	sleepTime=rand() % max_sleep_time +1;
  	printf("\nProducer: Sleep for %ds\n",sleepTime);
    sleep(sleepTime);
    (* shelf)++;
    printf("Producer: Item#%d\n", * shelf);
  }
  printf("Producer: Time is up. %d item produced. %d are left.\n", loop, * shelf);
  /* close and unlink shared memory*/
  munmap(shelf, sizeof(int));
  close(shm_fd);
  shm_unlink(name);
  return 0;
}

