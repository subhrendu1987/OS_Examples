/* 
 * File:   pipe_example.c
 * Author: subhrendu
 *
 * Created on 10 November, 2012, 1:05 PM
 */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
    int fd[2];
    pid_t childpid;
    pipe(fd);
    childpid=fork();
    if (childpid == -1)
    {
        perror("Error forking...");
        exit(1);
    }
    if (childpid)   /*parent proces*/   //grep .c
    {
        wait(&childpid);        //waits till the child send output to pipe
        close(fd[1]);
        close(0);       //stdin closed
        dup2(fd[0],0);
        execlp(argv[2],argv[2],argv[3],NULL);

    }
    if (childpid==0)  //ls
    {
        close(fd[0]);   /*Closes read side of pipe*/
        close(1);       //STDOUT closed
        dup2(fd[1],1);
        execlp("ls","ls","-l",NULL);
    }
    return 0;
}