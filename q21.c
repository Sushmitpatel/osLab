//que 3.1:-Write  a  program  in  C  that  creates  a  child  process,  waits  for  the termination  of  the  child  and  lists process  ID  (PID),  together  with  the  state  in  which  the  process  was  terminated  (in  decimal  and hexadecimal).
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    int pid;
    pid=fork();
    if(pid<0){
        printf("error");
        return 0;
    }
    if(pid>0){
        wait(NULL);
      printf("enter in parent process");
      printf("%d\n",pid);
    }
    else{
        printf("enter in child process\n");
        printf("%d",getpid());
        
    }
    return 0;
}