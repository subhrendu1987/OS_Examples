/* 
 * File:   history.c
 * Author: subhrendu
 *
 * Created on 9 November, 2012, 9:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
extern char **environ;
/******************************************************************************/
void comm_history(){
    char p[100];
    FILE *fp;
    char buffer;
    sprintf(p,ENV_BIN);
    strcat(p,"HISTORY.log");
    
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
    setShell(environ);
    comm_history();
    return (EXIT_SUCCESS);
}

