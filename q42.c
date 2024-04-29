//Que 4.2:-Write a  programin  CwhereaParentprocess  communicates  with its child process  via  pipecommandsuch that upon  receipt  of  the  message, the  child process changes  its  case  and  returns  the  message  (via  a  pipe)  to  the  parent, where  it  is  then  displayed. Note: On  a  system  that  does  not  support  duplex pipes, you will need to generate two pipes prior to forking the child process.
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
void changeCase(char *message){
 int n=strlen(message);
 int diff='A'-'a';
 for(int i=0;i<n;i++){
    if(message[i]<='z' && message[i]>='a'){
        message[i]+=diff;
    }
    else if(message[i]<='Z' && message[i]>='A'){
        message[i]-=diff;
    }
 }

}
int main(){
    int fd1[2],fd2[2];//fd1 for parent writing fd2 for child
    if(pipe(fd1)<0||pipe(fd2)<0){
        printf("error");
        return 0;
    }
    int pid=fork();
    if(pid<0){
        printf("error");
        return 0;
    }
    if(pid){
       close(fd2[1]);
       close(fd1[0]);
       char *message="helloAHELLo";
       write(fd1[1],message,strlen(message));
       close(fd1[1]);
        wait(NULL);
        char newmessage[100];
       read(fd2[0],newmessage,sizeof(newmessage));
       printf("%s",newmessage);
       close(fd2[0]);
      
    }
    else{
        close(fd1[1]);
        close(fd2[0]);
        char message[100];
        read(fd1[0],message,sizeof(message));
        close(fd1[0]);
        changeCase(message);
        //   printf("%s",message);
        write(fd2[1],message,sizeof(message));
        close(fd2[1]);

    }
    return 0;
}