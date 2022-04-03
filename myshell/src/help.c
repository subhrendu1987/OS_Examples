/* 
 * File:   help.c
 * Author: subhrendu
 *
 * Created on 26 October, 2012, 2:26 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
/*
 * 
 */

//extern char **environ;


/******************************************************************************/
void comm_help(int argv,char **argp){
    COMMAND *com;
    //char *argp;
    int count=0;
    if(argv==1){
        printf("sl\tcommand\t info\n");
        printf("--------------------\n");
        while(commands[count].name!=NULL){
            printf("[%d]\t%s-\t-[%s]\n",count,commands[count].name,commands[count].doc);
            count++;
        }
        return;
    }
    for(count=1;count<argv;count++){
        com=findCommand(*(argp+count));
        //printf("com==%p  com->doc=%p\n",com,com->doc);
        if(com!=NULL){
             printf("%s\n",(com->doc));
        }
    }
    return;
}
/******************************************************************************/
int main(int argc, char** argv) {
    comm_help(argc,argv);
    return (EXIT_SUCCESS);
}

