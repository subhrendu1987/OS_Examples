/* 
 * File:   initShell.c
 * Author: subhrendu
 *
 * Created on 30 October, 2012, 1:03 PM
 */

#include <stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

#include "main_header.h"
/*
 * 
 */
void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("received SIGINT\n");
  
}
/******************************************************************************/
int main(void){                        //(int argc, char** argv) {
    pid_t cpid, w;
    int status,success;
    char path[50];
    if (signal(SIGINT, sig_handler) == SIG_ERR){
        printf("\ncan't catch SIGINT\n");
    }
    while(1){
    cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /// Code executed by child 
               printf("Child PID is %ld\n", (long) getpid());
               sprintf(path,ENV_BIN);
               strcat(path,"shell.out");
               //success=execvpe(path,NULL,ENV);
               success=execlp(path,"shell.out",NULL);
               printf("--------------------\n");
               if(success < 0){
                   printf("%d  ",success);
                   perror("ERROR!IN EXECUTION");
                   //exit(EXIT_FAILURE);
               }else{
                   //exit(EXIT_SUCCESS);
               }
           } else {                    /// Code executed by parent 
               do {
                   w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(status)) {
                       printf("exited, status=%d\n", WEXITSTATUS(status));
                   } else if (WIFSIGNALED(status)) {
                       printf("killed by signal %d\n", WTERMSIG(status));
                   } else if (WIFSTOPPED(status)) {
                       printf("stopped by signal %d\n", WSTOPSIG(status));
                   } else if (WIFCONTINUED(status)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(status));
               //} while (!WIFEXITED(status) && !WIFSIGNALED(status));
           }
    }
    return (EXIT_SUCCESS);
}

