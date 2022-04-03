/* 
 * File:   man.c
 * Author: subhrendu
 *
 * Created on 8 November, 2012, 1:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
extern char **environ;

int main(int argc, char** argv) {
    FILE *fp;
    char buffer;
    char path[100];
    setShell(environ);
    if(argc>2){
        printf("One manual at a time\n");
        exit(0);
    }
    if(argc<2){
        printf("Which manual do you want\n");
        exit(0);
    }
    sprintf(path,ENV_BIN);
    strcat(path,"man/");
    strcat(path,*(argv+1));
    strcat(path,".man");
    //printf("path=%s\n",path);
    fp=fopen(path,"r");
    if(fp==NULL){
        printf("NO MANUAL FOUND\n");
        exit(0);
    }
    while(fscanf(fp,"%c",&buffer)!=EOF){
        printf("%c",buffer);
    }
    fclose(fp);

    return (EXIT_SUCCESS);
}

