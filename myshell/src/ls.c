/* 
 * File:   ls.c
 * Author: subhrendu
 *
 * Created on 25 October, 2012, 11:29 PM
 */
extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
/******************************************************************************/
void comm_ls(int argv,char **argp){
  DIR           *d;
  int count;
  struct dirent *dir;
  char* arg;
  char path[100];
  setShell(environ);
  printf("PWD=%s\n",ENV_PWD);
  //showArg(argv,argp);
  if(argv==1){                               ///DEFAULT
      path[0]='\0';
      sprintf(path,ENV_PWD);
      strcat(path,".");
      d = opendir(path);
      //printf("\n%s\n",path);
      //printf("------------------\n");
        if (d)
        {
          while ((dir = readdir(d)) != NULL)
          {
             if(dir->d_name[0]!='.'){
                  printf("%s", dir->d_name);
                  if(dir->d_type==4){   ///directory
                      printf("/\n");
                  }else{
                      printf("\n");
                  }
              }
              else{
                  //printf("[%s]\n", dir->d_name);    ///Hidden files
              }
          }
          printf("\n");
          closedir(d);
        }else{
            printf("%s\n",path);
            perror ("!(ls)ERROR");
        }
    }else{
      //printf("%d arguments\n",argv);
        for(count=1;count<argv;count++){
           arg=*(argp+count);
           path[0]='\0';
           if((*arg)!='/'){                              ///RELATIVE
              sprintf(path,ENV_PWD);
              strcat(path,arg);
          }else{                                         ///ABSOLUTE
              sprintf(path,arg);
          }
          strcat(path,".");
          d = opendir(path);
          printf("%s\n",path);
          printf("------------------\n");
          if (d)
          {
            while ((dir = readdir(d)) != NULL)
            {
                if(dir->d_name[0]!='.'){
                    printf("%s\n", dir->d_name);
                }
                else{
                    //printf("[%s]\n", dir->d_name);    ///Hidden files
                }
            }
            printf("\n");
            closedir(d);
          }else{
              perror ("!(ls)ERROR");
          }
        }
    }
  
  return;
}
/******************************************************************************/
int main(int argc,char **argv) {
    char *command;
    char *temp;
    int success;
    //temp=;
    //argv=getArguments(temp,&arguments);
    success=removeBackslash(argc,argv);
    //printf("BackslashRemoved\n");
    argc=removeNullArg(argc,argv);
    //printf("NullArgRemoved\n");
    //showArg(argc,argv);
    comm_ls(argc,argv);
    return (EXIT_SUCCESS);
}
   
