/* 
 * File:   create.c
 * Author: subhrendu
 *
 * Created on 2 November, 2012, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
FILE *fp;
/******************************************************************************/
void sig_handler(int signo)
{
  if (signo == SIGINT){
      printf("____________\n");
      printf("Stopped Recording\n");
      fclose(fp);
  }
exit(0);
}
/******************************************************************************/
int main(int argc, char** argv) {
    char file[100];
    char ch;
    if((argc==1)||(argc>2)){
        printf("USAGE:create filename\n");
        return (EXIT_SUCCESS);
    }
    //sprintf(file,)
    fp=fopen(*(argv+1),"w");
    if(fp==NULL){
        printf("ERROR!Opening file\n");
        return (EXIT_SUCCESS);
    }
    ch=getchar();
    signal(SIGINT, sig_handler);
    while((ch!=EOF)||(ch!=0)){
        ch=getchar();
        fprintf(fp,"%c",ch);
    }
    return (EXIT_SUCCESS);
}

