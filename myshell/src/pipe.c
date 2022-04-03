/* 
 * File:   pipe.c
 * Author: subhrendu
 *
 * Created on 27 October, 2012, 7:55 PM
 */
extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include "commands.h"

//#define PIPE_LIMIT 10                   /// limit is 9
/*
 * 
 */
/******************************************************************************/
int removeExtra(int A,char *pos[]){
    
}
/******************************************************************************/
int getArgument1(char *C,char *pos[]){
    int count;
    int i,length;
    count=0;
    pos[count]=C;
    count++;
    length=strlen(C);
    for(i=0;i<length;i++){
        if(*(C+i)==' '){
            if(*(C+i-1)!='\\'){
                *(C+i)='\0';
                pos[count]=(C+i+1);
                if(strlen(pos[count])!=0){
                        count++;
                }
            }
        }
    }
   // for(i=0;i<count;i++){
   //     printf("[%d] %s\n",i,pos[i]);
   // }
    //printf("%p",&pos);
    return(count);
}

/******************************************************************************/
int commandProcessorPipe(char *C,char *pos[]){
    int count;
    int i,length;
    char *t;
    t=strchr(C,'|');
    t=strchr(t+1,'|');
    if(t!=NULL){
        printf("BAD syntax near | \n");
        return(0);
    }
    count=0;
    pos[count]=C;
    count++;
    length=strlen(C);
    for(i=0;i<length;i++){
        if(*(C+i)=='|'){
            *(C+i)='\0';
            pos[count]=(C+i+1);
            if(strlen(pos[count])!=0){
                count++;
            }
        }
    }
    //printf("%p",&pos);
    return(count);
}

/******************************************************************************/
int main(int argc, char** argv) {
    char *base;
    COMMAND *com;
    pid_t cpid, w;
    int status,success;
    int silent;
    int count,i;
    //base=*arg;
    char command[100];
    char path[100];
    char *argV[MAX_ARGS];
    int *v;
    int N;
    if(argc<2){
        return (EXIT_SUCCESS);
    }
    setShell(environ);
    
    sprintf(command,*(argv+1));
    //printf("pipe=%s\n",command);
    N=commandProcessorPipe(command,argV);
    //printf("\nALL COMMANDS\n");
    if(N==0){
        exit(0);
    }
    //showArg(N,argV);
    //printf("%d\n",N);
    char *temp[N][MAX_ARGS];
    int arguc[N];
    count=0;
    for(count=0;count<N;count++){
        for(i=0;i<MAX_ARGS;i++){
            temp[count][i]=NULL;
        }
    }
    for(count=0;count<N;count++){
        //printf("COUNT=%d\n",count);
        arguc[count]=getArgument1(*(argV+count),temp[count]);
        //removeExtra(arguc[count],temp[count]);
        //printf("%d\n",arguc[count]);
        //showArg(arguc[count],temp[count]);  ///important
    }
        /******************************************/
     int pipe_file_descr[2];
     pipe(pipe_file_descr);
     //sprintf(path,ENV_BIN);
                    
     //printf("Parent PID is %ld\n", (long) getpid());

     cpid = fork();
     if(cpid!=0) {      ///parent
      
      base=*temp[1];
      com=findCommand(base);
      sprintf(path,ENV_BIN);
      strcat(path,com->exe);
      printf("Parent PID is %ld\n", (long) getpid());
     // printf("PARENT\n");
      //printf("1. ENV_PWD=%s\n",ENV_PWD);
      
      close(1);
      dup(pipe_file_descr[1]);
      close(pipe_file_descr[0]);
      
      
      success=execvpe(path,temp[1],ENV);
      //execlp("ls", "ls", "-1", NULL);
     } else {           ///child
      setShell(environ);
      base=*temp[0];
      com=findCommand(base);
      sprintf(path,ENV_BIN);
      strcat(path,com->exe);
      
      close(0);
      dup(pipe_file_descr[0]);
      //close(pipe_file_descr[1]);
      printf("Child PID is %ld\n", (long) getpid());
      //printf("CHILD\n");
      //printf("2. ENV_PWD=%s\n",ENV[2]);
      success=execvpe(path,temp[0],ENV);
      //execlp("wc","wc","-l",NULL);
      //execlp("cat", "cat", NULL);
     }
    
    
    
     if(!success){
         perror("ERROR!\n");
     }
    
    return(0);
}
    
