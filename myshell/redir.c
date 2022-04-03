#include "commands.h"

extern char **environ;

int output=-1;
int input=-1;
/******************************************************************************/
char* getIN(int argc,char **argv){
    int count;
    for(count=0;count<argc;count++){
        if(strcmp(*(argv+count),"<")==0){
            input=count;
            
            *(argv+count)=NULL;
            
            return(*(argv+count+1));
        }
    }
    return((char*)NULL);
}
/******************************************************************************/
char* getOUT(int argc,char **argv){
    int count;
    if(input==-1){
        count=0;
    }else{
        count=input+1;
    }
    for(;count<argc;count++){
        //printf("getOut()%s argc=%d count=%d\n",*(argv+count),argc,count);
        if(strcmp(*(argv+count),">")==0){
            output=count;
            
            *(argv+count)=NULL;
            
            return(*(argv+count+1));
        }
    }
    return((char*)NULL);
}
/******************************************************************************/
int getNewArgc(){
    int ret;
    if((input==-1)&&(output==-1)){
        printf("BAD SYNTAX, COMMAND < INFILE OUTFILE\n");
        exit(0);
    }else if(input==-1){
        return(output);
    }else if(output==-1){
        return(input);
    }else{
        ret=(input<output?input:output);
        return(ret);
    }
}

/******************************************************************************/
int main(int argc,char **argv){
int new_argc;
int success,status;
setShell(environ);
//showArg(argc,argv);
char *base;

char *OutFile;
char *InFile;
char *COMMAND;
char tempIN[100];
char tempOUT[100];

InFile=getIN(argc,argv);
//printf("InFile=%s\n",InFile);
OutFile=getOUT(argc,argv);

COMMAND=*(argv+1);

new_argc=delArguments(argc,&argv,0);

if(InFile!=NULL){
    sprintf(tempIN,ENV_PWD);
    strcat(tempIN,InFile);
    //printf("INPUT=%s\n",tempIN);
}

if(OutFile!=NULL){
    sprintf(tempOUT,ENV_PWD);
    strcat(tempOUT,OutFile);
    //printf("OUTPUT=%s\n",tempOUT);
}


/////////INPUT REDIRECTION

if(InFile!=NULL){
    input=open(tempIN,O_RDONLY,S_IREAD);
    if(input<0){
        printf("ERROR\n");
    }

    if(close(STDIN_FILENO)<0){
        close(input);
        exit(0);
    }
    
    if (dup(input) != STDIN_FILENO) {
    printf("dup(input)=%d  STDOUT_FILENO=%d\n",dup(input),STDOUT_FILENO);
            perror("dup(2)INFILE");
            close(input); 
            exit(EXIT_FAILURE);
    }
    close(input);
}


////////OUTPUT REDIRECTION
if(OutFile!=NULL){
    output=open(tempOUT,O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRGRP|S_IROTH);
    if(output<0){
        printf("ERROR\n");
    }

    if(close(STDOUT_FILENO)<0){
        close(output);
        exit(0);
    }
    if (dup(output) != STDOUT_FILENO) {
            perror("dup(2)OUTFILE");
            close(output); 
            exit(EXIT_FAILURE);
    }
    close(output);
}
base=*argv;
if((*base=='.')&&(*(base+1)=='/')){       ///     
    printf("path=%s\n",(base+2));
        success=createProcess((base+2),argv);
        if(success < 0){
                printf("%d  ",success);
                perror("RUN EXECUTABLE ERROR!");
        }else{                                                      ///     ./
        printf("Nothing to execute\n");
    }
}else{
    success=commandExecute(new_argc,argv,0);
    
}
if(success < 0){
        printf("%d  ",success);
        perror("COMMAND ERROR!");
    }

}
