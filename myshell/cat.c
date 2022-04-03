/* 
 * File:   cat.c
 * Author: subhrendu
 *
 * Created on 28 October, 2012, 11:01 PM
 */
extern char** environ;

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
/******************************************************************************/
void comm_cat(char *path){
    char p[100];
    FILE *fp;
    char buffer;
    if(*path=='/'){     ///absolute path
        sprintf(p,path);
    }else{              ///relative path
        sprintf(p,ENV_PWD);
        strcat(p,path);
    }
    //printf("-------------\n");
    //printf("%s\n",p);
    //printf("-------------\n");
    fp=fopen(p,"r");
        if(fp==NULL){
            printf("(cat)ERROR! FILE NOT FOUND[%s]\n",p);
        }
        while(fscanf(fp,"%c",&buffer)!=EOF){
            printf("%c",buffer);
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
    //printf("PWD=%s\n",ENV_PWD);
    int i;
    //showArg(argc,argv);
    for(i=1;i<argc;i++){
        comm_cat(*(argv+i));
    }
    return (EXIT_SUCCESS);
}

