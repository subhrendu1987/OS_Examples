/* 
 * File:   pwd.c
 * Author: subhrendu
 *
 * Created on 26 October, 2012, 12:39 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */

extern char **environ;

void comm_pwd(int argv,char **argp){
    setShell(environ);
    printf("PWD\n");
    printf("PWD=%s\n",ENV_PWD);
}

int main(int argc, char** argv) {
    comm_pwd(argc,argv);
    return (EXIT_SUCCESS);
}

