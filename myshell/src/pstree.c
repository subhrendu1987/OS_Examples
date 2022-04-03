/* 
 * File:   pstree.c
 * Author: subhrendu
 *
 * Created on 29 October, 2012, 9:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "main_header.h"
/*
 * 
 */
#define MAX_PROC 1000
#define SIZE 10


char name[MAX_PROC][50];
char pid[MAX_PROC][SIZE];
char status[MAX_PROC][SIZE];
char ppid[MAX_PROC][SIZE];
int  level[MAX_PROC]={0};
int done[MAX_PROC]={0};
int temp=0;

/******************************************************************************/
void viewN(int count){
    int i;
    printf("(%d).",temp);
    temp++;
    for(i=0;i<level[count];i++){
          printf("\t");
    }
    printf("|-{%s}(%s)",ppid[count],pid[count]);
    printf("%s[%s]\n",name[count],status[count]);
}
/******************************************************************************/
void view(int N){
    int count;
    
    printf("|-{PPID}(PID)");
    printf("(NAME)[STATUS]\n");
    for(count=0;count<N;count++){
        viewN(count);
    }
    return;
}
/******************************************************************************/
int getLevel(int n){
    int count;
    for(count=n;count>=0;count--){
        if(strcmp(ppid[n],"0")==0){
            return(1);
        }else if(strcmp(ppid[n],pid[count])==0){
            return(level[count]+1);
        }
    }
    
}
/******************************************************************************/
void getAllLevel(int N){
    int count;
    for(count=0;count<N;count++){
        level[count]=getLevel(count);
    }
}
/******************************************************************************/
void getParameter(int N){
    int count;
    char path[50];
    char buffer[SIZE];
    FILE *fp;
    for(count=0;count<N;count++){
        sprintf(path,"/proc/");
        strcat(path,pid[count]);
        strcat(path,"/stat");
        //printf("path=%s\n",path);
                ///3393 (gnome-pty-helpe) S 3386 1740 1740 0
        fp=fopen(path,"r");
        fscanf(fp,"%s",buffer);         ///PID
        fscanf(fp,"%s",name[count]);    ///NAME
        fscanf(fp,"%s",status[count]);  ///STATUS
        fscanf(fp,"%s",ppid[count]);    ///PPID
        fclose(fp);
    }
    return;
}
/******************************************************************************/
void swap(int i,int j){
    char temp[SIZE];
    int tempN;
    ///PID
    sprintf(temp,pid[i]);
    sprintf(pid[i],pid[j]);
    sprintf(pid[j],temp);
    ///NAME
    sprintf(temp,name[i]);
    sprintf(name[i],name[j]);
    sprintf(name[j],temp);
    ///STATUS
    sprintf(temp,status[i]);
    sprintf(status[i],status[j]);
    sprintf(status[j],temp);
    ///PPID
    sprintf(temp,ppid[i]);
    sprintf(ppid[i],ppid[j]);
    sprintf(ppid[j],temp);
    ///LEVEL
    tempN=level[i];
    level[i]=level[j];
    level[j]=tempN;
    return;
}
/******************************************************************************/
void sort(int N){
    int i,j;
    int ppidI,ppidJ,pid1;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            ppidI=atoi(ppid[i]);
            ppidJ=atoi(ppid[j]);
            if(ppidI<ppidJ){
                swap(i,j);
            }
        }
    }
    return;
}
/******************************************************************************/
int findChild(int start,int parent,int N){
    int count;
    for(count=(start);count<N;count++){
        if(atoi(ppid[count])==parent){
            if(done[count]==0){
                done[count]=1;
                return(count);
            }else{
            }
        }
    }
    return(-1);
}
/******************************************************************************/
void hierarchy(int index,int N){
    int i;
    if(index<N){
        if(index!=0){
            viewN(index);
        }
        while((i=findChild(0,atoi(pid[index]),N))!=-1){
            hierarchy(i,N);
        }
    }
}

/******************************************************************************/
int main(int argc, char** argv) {
    level[0]=0;
    char path[100];
    sprintf(path,"/proc/.");
    DIR           *d;
    struct dirent *dir;
    int count=0;
    int no_of_proc;
    
    d = opendir(path);
    //  printf("\npath=%s\n",path);
    printf("|-{PPID}(PID)");
    printf("(NAME)[STATUS]\n");
      printf("------------------\n");
        if (d){
          while ((dir = readdir(d)) != NULL){
             if(isdigit(dir->d_name[0])){
                  sprintf(&pid[count][0],dir->d_name);
                  count++;
              }
              else{
              }
          }
          no_of_proc=count;
          
          closedir(d);
          getParameter(no_of_proc);
          /*    ADD PROCESS WITH PID 0 */
                sprintf(&pid[no_of_proc][0],"0");         ///PID
                sprintf(&name[no_of_proc][0],"(DISPATCHER)");    ///NAME
                sprintf(&status[no_of_proc][0],"");  ///STATUS
                sprintf(&ppid[no_of_proc][0],"-1");    ///PPID
                level[no_of_proc]=0;
                no_of_proc++;
          
          sort(no_of_proc);
          //sprintf(&ppid[0][0]," ");    ///PPID
          //view(no_of_proc);
          getAllLevel(no_of_proc);
         // printf("level\n");
          hierarchy(0,no_of_proc);
          //generateTREE(no_of_proc);
          //view(no_of_proc);
          printf("NO OF PROCESS=%d\n",(no_of_proc-1));
        }else{
            perror ("!ERROR");
        }
    return (EXIT_SUCCESS);
}

