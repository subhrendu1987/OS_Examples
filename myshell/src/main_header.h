/* 
 * File:   main_header.h
 * Author: subhrendu
 *
 * Created on 23 October, 2012, 2:06 AM
 */

/* MAIN_HEADER_H */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>


#define BUFFER_SIZE 100
#define MAX_ARGS 10
#define NO_ENV 3

/************************ENVIRONMENT VARIABLE**********************************/
char *ENV[NO_ENV];
/**************************************/
char *ENV_SET;
char *ENV_PROMPT;
char *ENV_LOG_FILE;
char *ENV_PWD;
char ENV_SHELLPROMPT[100];

char ENV_BIN[]={"/media/USER_SPACE/NetBeansProjects/myshell/"};
/******************************************************************************/
void initializeShell(){
 //shmat(1,ENV_PROMPT);
 //shmat(2,ENV_LOG_FILE);
 //shmat(3,ENV_PWD);
 ENV_PROMPT=(char*)malloc(sizeof(char)*strlen("user@myshell"));
 sprintf(ENV_PROMPT,"user@myshell");
 ENV_LOG_FILE=(char*)malloc(sizeof(char)*strlen("HISTORY.log"));
 sprintf(ENV_LOG_FILE,"HISTORY.log");
 ENV_PWD=(char*)malloc(sizeof(char)*strlen("/home/subhrendu/"));
 sprintf(ENV_PWD,"/home/subhrendu/");
 return;       
}
/******************************************************************************/
/*void getShell(){
    ENV[0]=ENV_PROMPT;
    ENV[1]=ENV_LOG_FILE;
    ENV[2]=ENV_PWD;
}
/******************************************************************************/
/*void setShell(char **env){
    ENV_PROMPT=*env;
    ENV_LOG_FILE=*(env+1);
    ENV_PWD=*(env+2);
}
/******************************************************************************/
void fileScan(FILE *fp,char string[]){
    char ch;
    int count=0;
    fscanf(fp,"%c",&ch);
    while((ch!=EOF)&&(ch!='\n')){
        string[count]=ch;
        fscanf(fp,"%c",&ch);
        count++;
    }
    string[count]='\0';
    return;
}
/******************************************************************************/
void getShell(){
    FILE *fp;
    fp=fopen("/home/subhrendu/.profile","w");
    if(!fp){
        printf("FATAL ERRROR!Could not open profile\n");
        return;
    }
    char buff[100];
    fprintf(fp,"%s\n",ENV_PROMPT);
    fprintf(fp,"%s\n",ENV_LOG_FILE);
    fprintf(fp,"%s\n",ENV_PWD);
    fclose(fp);
   // ENV[0]=ENV_PROMPT;
   // ENV[1]=ENV_LOG_FILE;
   // ENV[2]=ENV_PWD;
}
/******************************************************************************/
void setShell(char **env){
    FILE *fp;
    fp=fopen("/home/subhrendu/.profile","r");
    
    if(!fp){
        printf("FATAL ERRROR!Could not open profile\n");
        return;
    }
    char buff[100];
        //fscanf(fp,"%s",buff);
        fileScan(fp,buff);
        ENV_PROMPT=(char *)malloc(sizeof(char)*strlen(buff));
        sprintf(ENV_PROMPT,buff);
        //fscanf(fp,"%s",buff);
        fileScan(fp,buff);
        ENV_LOG_FILE=(char *)malloc(sizeof(char)*strlen(buff));
        sprintf(ENV_LOG_FILE,buff);
        //fscanf(fp,"%s",buff);
        fileScan(fp,buff);
        ENV_PWD=(char *)malloc(sizeof(char)*strlen(buff));
        sprintf(ENV_PWD,buff);
    fclose(fp);
    //ENV_PROMPT=*env;
    //ENV_LOG_FILE=*(env+1);
    //ENV_PWD=*(env+2);
}
/******************************************************************************/
int addArguments(char *T,char ***argc,int argv){
    int count;
    if(argv>=MAX_ARGS-1){
        printf("USE LESS ARGUMENTS\n");
        return(0);
    }
    for(count=argv;count>0;count--){
        *(*argc+(count))=*(*argc+(count-1));
    }
    *(*argc+0)=T;
    return(argv+1);
}
/******************************************************************************/
int delArguments(int argv,char ***argc,int pos){
    int count;
    for(count=pos;count<argv;count++){
        *(*argc+(count))=*(*argc+(count+1));
    }
    return(argv-1);
}
/******************************************************************************/
int getArguments(char *T,char ***argv){
    int count;
    char* temp;
    *argv=(char**)malloc(sizeof(char*)*MAX_ARGS);
    for(count=0;count<MAX_ARGS;count++){
        *(*argv+count)=NULL;
    }
    if(T==NULL){
        printf("No arguments\n");
        return(0);
    }
    for(count=0;count<MAX_ARGS;count++){
        *(*argv+count)=T;
        //printf("[%d] %s\n",count,*(*argv+count));
        //printf("T--  %s\n",T);
        T=strchrnul(T,' ');
        if(*(T-1)!='\\'){
            if(*(T)=='\0'){
                break;
            }else{
                *T='\0';
                T++;
            }
         }else{         ///whitespaces handling
            temp=*(*argv+count);
            while(temp=strchrnul(temp,' ')){
                //printf("Temp--%s  (%c)\n",temp,*(temp-1));
                if((*(temp-1)=='\\')&&(*(temp)==' ')){
                    //printf("True\n");
                    if(*(temp)=='\0'){
                        goto label;
                    }else{
                        temp++;
                    }
                }else{
                    break;
                }
            }
            T=(temp);
            *temp='\0';
         }
    }
  label:  if(*T!='\0'){
        printf("no. of ARGUMENTS greater than 10\n");
        return(-1);
    }
  
  if(((count+1)==MAX_ARGS)){
    printf("no. of ARGUMENTS greater than 10\n");
    return(-1);
  }
  //printf("count=%d+1\n",count);
  if(**(*argv+count)<1){
      
      return(count);
  }
  return(count+1);
}
/******************************************************************************/
void showArg(int argv,char** argc){
    int count;
    char *last;
    char lastc;
    int silent=0;
    
    if(argv<1){
        last=*(argc+argv-1);
        lastc=*(last+strlen(last-1));
        if(lastc=='&'){
            printf("LAST ARGUMENT=%s\n",last);
            printf("lastc=%c\n",lastc);
            silent=1;
        }
        printf("SILENT=%d\n",silent);
    }
    if(argc!=NULL){
        for(count=0;count<argv;count++){
            printf("[%d] |%s|\n",count,*(argc+count));
        }
    }else{
        return;
    }
}
/******************************************************************************/
char* trim (char *string){
  register char *s, *t;

  for (s = string; whitespace (*s); s++){
  }
  if (*s == 0){
    return (s);
  }
  t = s + strlen (s) - 1;
  while (t > s && whitespace (*t)){
    t--;
  }
  *++t = '\0';
  return s;
}
/******************************************************************************/
int removeBackslash(int argv,char **argc){
    int count;
    char *argp;
    char *temp;
    if(argv>1){
        //printf("removeBackSlash\n");
        for(count=1;count<argv;count++){
            argp=*(argc+count);
            //printf("[%d] argp=%s\n",count,argp);
            temp=strrchr(argp,'\\');
            while(temp){
                if(temp!=NULL){
                    while(*temp!='\0'){
                        *temp=*(temp+1);
                        temp++;
                    }
                    temp=strrchr(argp,'\\');
                }
            }
            //printf("ARGP=%s\n",argp);
            
        }
    }
    return(0);
}
/******************************************************************************/
int removeNullArg(int argc,char **argv){
    if(argc>1){
        char *last;
        last=*(argv+(argc-1));
        //printf("last=%s\n",last);
        if(strcmp(last,"\0")==0){
            //*(*argv+(*argc-1))=NULL;
            argc=(argc -1);
            return(argc);
        }
    }
    return(argc);
}
/******************************************************************************/
showByte(char *s){
    int len=strlen(s);
    int count;
    for(count=0;count<len;count++) {
        printf("(%d) [%p]  %c\n",strlen(s+count),(s+count),*(s+count));
    }
}
