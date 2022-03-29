#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define max_sleep_time 10

const char * name = "shared_memory";
int shm_fd; //file descriptor of
int * shelf;
int loop=6;
int sleepTime;
unsigned int seedP=5;
unsigned int seedC=5;