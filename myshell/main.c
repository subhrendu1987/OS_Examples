/* 
 * File:   main.c
 * Author: subhrendu
 *
 * Created on 10 October, 2012, 3:51 PM
 */
#include "commands.h"

/*
 * 
 */
/******************************************************************************/
void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("\n%s",ENV_SHELLPROMPT);
  return;
}
/******************************************************************************/
int main() {
    int count;
    char *command;
    char *original;
    int total_size;
    char *base_command;
    //char *arguments[MAX_ARGS];
    char **arguments;
    char *temp;
    char *temp1;
    int argv;
    int pid;
    int success,silent;
    initializeShell();
    signal(SIGINT, sig_handler);
    while(1){
        silent=0;
        /*for(count=0;count<MAX_ARGS;count++){
            arguments[count]=NULL;
        }
         */ 
        getShell();
            ENV_SHELLPROMPT[0]='\0';
            strcat(ENV_SHELLPROMPT,ENV_PROMPT);
            strcat(ENV_SHELLPROMPT,":");
            strcat(ENV_SHELLPROMPT,ENV_PWD);
            strcat(ENV_SHELLPROMPT,"$");
            
            fflush(stdin);
            command=readline(ENV_SHELLPROMPT);
            total_size=strlen(original);
            add_history(command);
            writeTolog(command);
            //printf("COMMAND=%s\n",command);
            command=trim(command);
            if(command[strlen(command)-1]=='&'){
                //printf("silent\n");
                silent=1;
                command[strlen(command)-1]='\0';
            }
            temp=strchr(command,'|');
            temp1=strchr(command,'<');
            if(temp1==NULL){
                temp1=strchr(command,'>');
                if(temp1!=NULL){
                    if(!((*(temp1-1)==' ')&&(*(temp1+1)==' '))){
                        printf("BAD SYNTAX, COMMAND < INFILE OUTFILE\n");
                        continue;
                    }
                }
            }else{
                if(!((*(temp1-1)==' ')&&(*(temp1+1)==' '))){
                    printf("BAD SYNTAX, COMMAND < INFILE OUTFILE\n");
                    continue;
                }
            }
            if(temp==NULL && temp1==NULL){
                //char *temp[N][MAX_ARGS];
                //arguc[count]=getArgument1(*(argV+count),temp[count]);
                //argv=getArguments(command,arguments);
                argv=getArguments(command,&arguments);
                if(argv<1){
                    continue;
                }
                //showArg(argv,arguments);
                base_command=*(arguments);
                //printf("BASE COMMAND=%s argv=%d\n",base_command,argv);
                //printf("Test=%c%c  %s\n",*base_command,*(base_command+1),(base_command+2));
                //printf("_________________________________________________________________\n");
                if(strcmp(base_command,"quit")==0){                             ///     quit
                    comm_quit(0,(char**)NULL);
                }else if((*base_command=='.')&&(*(base_command+1)=='/')){       ///     ./___
                    if((*(base_command+2)>0)){
                        printf("EXECUTE %s\n",(base_command+2));
                        success=createProcess((base_command+2),arguments);
                        if(success < 0){
                                printf("%d  ",success);
                                perror("RUN EXECUTABLE ERROR!");
                        }
                    }else{                                                      ///     ./
                        printf("Nothing to execute\n");
                    }
                }else{                                                          ///     library commands
                    //showArg(argv,arguments);
                    success=commandExecute(argv,arguments,silent);
                    if(success < 0){
                   printf("%d  ",success);
                   perror("COMMAND ERROR!");
               }
                }
            }else if(temp!=NULL){                                                              ///     *|*
                //printf("PIPED PROCESS\n");
              //  success=pipedMain(command,temp);
                char path[5];
                sprintf(path,"pipe");
                char *ag[2];
                ag[0]=path;
                ag[1]=command;
                success=commandExecute(2,ag,silent);
                if(success < 0){
                   printf("%d  ",success);
                   perror("PIPE ERROR!");
               }
            }else{
                printf("Redirection\n");
                char C[]={"redirection"};
                base_command=C;
                argv=getArguments(command,&arguments);
                argv=addArguments(C,&arguments,argv);
                
                if(argv<1){
                    continue;
                }
                
                success=commandExecute(argv,arguments,silent);
                if(success < 0){
                   printf("%d  ",success);
                   perror("REDIRECTION ERROR!");
               }
            }
                ///////GARBAGE COLLECTOR
                bzero(command,total_size);
                free(command);
                //free(base_command);
                //free(arguments);
        
    }
    return (EXIT_SUCCESS);
}

