//que 4.1:-Write aCprogram to show parent child process relation using fork () system call  in  which  Parent  creates  pipe,  forks  a  child,  and  writes  into  pipe (thenumber  whose  factorial  is  to  be  calculated,  take  number  from  user),  Child reads from the pipe and compute and display factorial of a number written by parent process.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}
int main(){
    int fd[2];
    if(pipe(fd)<0){
        printf("error");
        return  0;
    }
    int pid=fork();
    if(pid<0){
        printf("error");
        return 0;
    }
    if(pid>0){
        int num;
        scanf("%d",&num);
        close(fd[0]);
        write(fd[1],&num,sizeof(num));
        close(fd[1]);
        wait(NULL);

    }
    else{
      int num;
      close(fd[1]);
      read(fd[0],&num,sizeof(num));
      close(fd[0]);
      printf("received\n");
      printf("fact of %d is: %d",num,factorial(num));
    }
    return 0;
}