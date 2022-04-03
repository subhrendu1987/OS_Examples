/* 
 * File:   EXECUTE.c
 * Author: subhrendu
 *
 * Created on 27 October, 2012, 11:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
#include "library.h"
extern char **environ;
/*
 * 
 */


/******************************************************************************/


/******************************************************************************/
COMMAND* findCommand(char *base){
    int i;
    for (i = 0; commands[i].name; i++){
        if (strcmp (base, commands[i].name) == 0){
           // printf("%p  %s\n",&commands[i],commands[i].doc);
            return(&commands[i]);
        }
        //printf("findCommand()--%s!=%s\n",base,commands[i].name);
    }
  return ((COMMAND *)NULL);
}
/******************************************************************************/
void comm_cd(int argv,char **argc){
    char *argp;
    char path[100];
    DIR           *d;
    struct dirent *dir;
    char *temp;
    removeBackslash(argv,argc);
    printf("BackslashRemoved\n");
    argv=removeNullArg(argv,argc);
    printf("NullArgRemoved\n");
    if(argv < 3){
        argp=*(argc+1);
        char *new_pwd,*temp;
        printf("arg=[%s]\n",argp);
        if(argv==1){
            new_pwd=(char*)malloc(sizeof(char)*(strlen("/home/subhrendu/")));
            sprintf(new_pwd,"/home/subhrendu/");
        }else if(*argp=='.'){              ///UP ONE LEVEL
            if(strcmp(ENV_PWD,"/")==0){
                return;
            }else{
                new_pwd=strrchr(ENV_PWD,'/');
                *new_pwd='_';
                //printf("%s\n",ENV_PWD);
                new_pwd=strrchr(ENV_PWD,'/');
                *new_pwd='\0';
                new_pwd++;
                strcat(ENV_PWD,"/");
               // printf("ENV=PWD%s  new_pwd=%s\n",ENV_PWD,new_pwd);

                temp=new_pwd;
                new_pwd=ENV_PWD;
                ENV_PWD=NULL;
            }
        }else if(*(argp)=='/'){                   ///ABSOLUTE
            new_pwd=(char*)malloc(sizeof(char)*strlen(argp));
            sprintf(new_pwd,argp);
        }else if(*(argp)!='/'){                   ///relative
            new_pwd=(char*)malloc(sizeof(char)*(strlen(argp)+strlen(ENV_PWD)));
            sprintf(new_pwd,ENV_PWD);
            strcat(new_pwd,argp);
        }
        path[0]='\0';
        sprintf(path,new_pwd);                   /////check for proper Directory
        strcat(path,".");
        d = opendir(path);
        if(d){
            closedir(d);
            if(!ENV_PWD){
                free(ENV_PWD);
            }
            ENV_PWD=new_pwd;
            getShell();
        }else{
            printf("ERROR![%s]\n",path);
            perror("");
        }
       // printf("ENV_PWD=%s\n",ENV_PWD);
    }else{
        printf("TOO MANY ARGUMENTS\n");
    }
}
/******************************************************************************/
int commandExecute(int argv,char **arg){
    char *base;
    COMMAND *com;
    pid_t cpid, w;
    int status,success;
    int silent;
    base=*arg;
    char path[100];
    com=findCommand(base);
    if(com==NULL){
        printf("NO SUCH COMMAND FOUND\n");
        return(-1);
    }else if(strcmp(com->name,"cd")==0){
         comm_cd(argv,arg);
    /*}else if(strcmp(com->name,"pwd")==0){
        comm_pwd(argv,arg);*/
    }else{                              ///parent - child structure
           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /// Code executed by child 
               printf("Child PID is %ld\n", (long) getpid());
               printf("--------------------\n");
               sprintf(path,ENV_BIN);
               strcat(path,com->exe);
               success=execvpe(path,arg,ENV);
               //success=execv(com->exe,arg);
               printf("--------------------\n");
               if(success < 0){
                   printf("%d  ",success);
                   perror("ERROR!IN EXECUTION");
                   exit(EXIT_FAILURE);
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
                      // printf("exited, status=%d\n", WEXITSTATUS(status));
                   } else if (WIFSIGNALED(status)) {
                       printf("killed by signal %d\n", WTERMSIG(status));
                   } else if (WIFSTOPPED(status)) {
                       printf("stopped by signal %d\n", WSTOPSIG(status));
                   } else if (WIFCONTINUED(status)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(status) && !WIFSIGNALED(status));
               return(0);
           }
    }
}


/******************************************************************************/
int main(int argc, char** argv) {
    char *command;
    char *temp;
    int success;
    ///if(environ ==garbage then)}
    ///initializeShell(environ);
    ///getShell();
    ///}else{
    setShell(environ);
    
    commandExecute(argc,(argv+1));
    return (EXIT_SUCCESS);
}

