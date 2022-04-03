/* 
 * File:   cd.c
 * Author: subhrendu
 *
 * Created on 27 October, 2012, 6:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"

/*
 * 
 */
extern char **environ;

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
        printf("ENV_PWD=%s\n",ENV_PWD);
    }else{
        printf("TOO MANY ARGUMENTS\n");
    }
}
/******************************************************************************/

int main(int argc, char** argv) {
    char *command;
    char *temp;
    int success;
    //temp=;
    //argv=getArguments(temp,&arguments);
    setShell(environ);
    success=removeBackslash(argc,argv);
    //printf("BackslashRemoved\n");
    argc=removeNullArg(argc,argv);
    //printf("NullArgRemoved\n");
    comm_cd(argc,argv);
    return (EXIT_SUCCESS);
}

