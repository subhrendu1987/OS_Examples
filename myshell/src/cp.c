#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_header.h"
#define MAX 10

extern char **environ;

int main(int argc, char *argv[MAX]) { 
    setShell(environ);
    int c;
    FILE *fp_src, *fp_dst;
    char path1[100];
    char path2[100];
    
         
        
	if(argc<3){
            printf("ERROR!cp source destination\n");
            exit(0);
        }
    if(*(argv[1])=='/'){     ///absolute source path
        sprintf(path1,argv[1]);
         }else{              ///relative source path
        sprintf(path1,ENV_PWD);
        strcat(path1,argv[1]);
    }
    if(*(argv[2])=='/'){     ///absolute dest path
        sprintf(path2,argv[2]);
         }else{              ///relative dest path
        sprintf(path2,ENV_PWD);
        strcat(path2,argv[2]);
    }
    
	fp_src=fopen(path1, "r");
	if(fp_src==NULL){
            printf("ERROR! Opening source file\n");
            exit(0);
        }
	fp_dst=fopen(path2, "w");
	if(fp_src==NULL){
            printf("ERROR! Opening Destination file\n");
            exit(0);
        }
   	
   	c = getc(fp_src) ;
   	while(c!= EOF)
     	{
     		putc(c, fp_dst);
     		c=getc(fp_src);
     	}
  	fclose(fp_src);
  	fclose(fp_dst);
 
   	return 0;
   }
   	
   	