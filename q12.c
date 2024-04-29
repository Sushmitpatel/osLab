// que 2:- Write a program to read some content (20 characters) of file F1.txt into file F2.txt. The contents of file F2 should not get deleted or overwritten.
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
    char buffer[20];
    ssize_t rd_bytes,wr_bytes;
    int fd1,fd2;
    fd1=open("f1.txt",O_RDONLY);
    if(fd1==-1){
       
        printf("some error occured");
        close(fd1);
        return 0;
    }
    fd2=open("f2.txt",O_WRONLY|O_APPEND|O_CREAT,0664);
    if(fd2==-1){
         printf("h\n");
        printf("some error occured");
        close(fd2);
        return 0;
    }
    rd_bytes=read(fd1,buffer,20);
    if(rd_bytes==-1){
        printf("some error occured");
        close(fd1);
        close(fd2);
        return 0;
    }
    wr_bytes=write(fd2,buffer,rd_bytes);
    close(fd1);
    close(fd2);
    return 0;

}


