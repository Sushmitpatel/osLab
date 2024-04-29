//Que 5:- Write a program to print characters starting from 15th character till the 20th character of file F1.txt into the file   F2.txt. 
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    char buffer[6];
    int fd1=open("f1.txt",O_RDONLY);
    int fd2=open("f2.txt",O_WRONLY|O_APPEND|O_CREAT,0664);
    if(fd1<0){
        printf("error");
        return 0;
    }
    int offset=lseek(fd1,14,SEEK_SET);
    if(offset<0){
        printf("error");
        close(fd1);
        close(fd2);
        return 0;
    }
    int r_bytes=read(fd1,buffer,6);
    if(r_bytes<0){
        printf("error");
        close(fd1);
        close(fd2);
        return 0;
    }
    int wr_bytes=write(fd2,buffer,r_bytes);
    if(wr_bytes<0){
        printf("error");
        close(fd1);
        return 0;
    }
    close(fd1);
    close(fd2);
    return 0;

}