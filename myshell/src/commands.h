/* 
 * File:   commands.h
 * Author: subhrendu
 *
 * Created on 10 October, 2012, 3:52 PM
 */

#include "main_header.h"
#include "library.h"

/******************************************************************************/
COMMAND* findCommand(char *base){
    int i;
    for (i = 0; commands[i].name; i++){
        if (strcmp (base, commands[i].name) == 0){
            return(&commands[i]);
        }
    }
  return ((COMMAND *)NULL);
}
/******************************************************************************/
void writeTolog(char com[]){
    FILE *fp;
    fp=fopen(ENV_LOG_FILE,"a");
    fprintf(fp,"%s\n",com);
    fclose(fp);
}
/******************************************************************************/
int commandExecute(int argv,char **arg,int silent){
    char *base;
    COMMAND *com;
    pid_t cpid, w;
    int status,success;
    base=*arg;
    char path[100];
    com=findCommand(base);
    if(com==NULL){
        printf("NO SUCH COMMAND FOUND [%s]\n",base);
        return(0);
    }else if(strcmp(com->name,"cd")==0){
         comm_cd(argv,arg);
    }else{                              ///parent - child structure
           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }
           if (cpid == 0) {            /// Code executed by child 
               //printf("Child PID is %ld\n", (long) getpid());
               sprintf(path,ENV_BIN);
               strcat(path,com->exe);
               //arg[0]="redir.out";
               //strcat(arg[0],".out");
                //printf("(commandExecute)path=%s\n",path);
               success=execvpe(path,arg,ENV);
               if(success < 0){
                   printf("PATH=%s\n",path);
                   printf("ARG0=%s\n",arg[0]);
                   printf("ARG1=%s\n",arg[1]);
                   perror("ERROR!IN EXECUTION");
                   exit(EXIT_FAILURE);
               }else{
                   exit(EXIT_SUCCESS);
               }
           } else if(silent==0){                    /// Code executed by parent 
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
           }else{
               return(0);
           }
    }
}


/******************************************************************************/
int createProcess(int argv,char **arg){
    char *base;
    COMMAND *com;
    pid_t cpid, w;
    int status,success;
    int silent;
    base=*arg;
                                 ///parent - child structure
           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /// Code executed by child 
               //printf("Child PID is %ld\n", (long) getpid());
               success=execv(base,arg);
               if(success < 0){
                   perror("ERROR!IN EXECUTION");
                   exit(EXIT_FAILURE);
               }else{
                   exit(EXIT_SUCCESS);
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

/******************************************************************************/

void comm_cd(int argv,char **argc){
    char *argp;
    char path[100];
    DIR           *d;
    struct dirent *dir;
    char *temp;
    removeBackslash(argv,argc);
    argv=removeNullArg(argv,argc);
    if(argv < 3){
        argp=*(argc+1);
        char *new_pwd,*temp;
        //printf("arg=[%s]\n",argp);
        if(argv==1){
            new_pwd=(char*)malloc(sizeof(char)*(strlen("/home/subhrendu/")));
            sprintf(new_pwd,"/home/subhrendu/");
        }else if(*argp=='.'){              ///UP ONE LEVEL
            if(strcmp(ENV_PWD,"/")==0){
                return;
            }else{
                new_pwd=strrchr(ENV_PWD,'/');
                *new_pwd='_';
                new_pwd=strrchr(ENV_PWD,'/');
                *new_pwd='\0';
                new_pwd++;
                strcat(ENV_PWD,"/");

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
void comm_quit(int argv,char **argp){
    pid_t self,parent;
    self=getpid();
    parent=getppid();
    //printf("KILL %d  %d\n",parent,self);
    printf("EXIT FROM SHELL\n");
    exit(0);
}
/******************************************************************************/

/******************************************************************************/
