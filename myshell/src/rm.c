/* 
 * File:   rm.c
 * Author: subhrendu
 *
 * Created on 29 October, 2012, 12:02 AM
 */
extern char **environ;
#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
/******************************************************************************/
void comm_rm(char *path){
    char p[100];
    int ret;
    char buffer;
    if(*path=='/'){     ///absolute path
        sprintf(p,path);
    }else{              ///relative path
        sprintf(p,ENV_PWD);
        strcat(p,path);
    }
    printf("-------------\n");
    printf("%s\n",p);
    printf("-------------\n");
    ret=remove(p);
    if(ret<0){
        printf("ERROR!Cannot remove file\n");
    }
    return;
}
/******************************************************************************/
int main(int argc, char** argv) {
    if(argc<2){
        printf("ERROR!Expected filename\n");
        return (EXIT_SUCCESS);
    }
    setShell(environ);
    printf("PWD=%s\n",ENV_PWD);
    int i;
    showArg(argc,argv);
    for(i=1;i<argc;i++){
        comm_rm(*(argv+i));
    }
    return (EXIT_SUCCESS);
}

