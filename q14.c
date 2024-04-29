// Que-4:-Write a program using open () and lseek () system calls to print the last 5 characters of a file on the screen. 
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
    char buffer[6];
    int r_bytes,fd;
    int offset;
    fd=open("merged.txt",O_RDONLY);
    if(fd==-1){
        printf("error");
        return 0;
    }
    offset=lseek(fd,-5,SEEK_END);
    if(offset==-1){
        close(fd);
        printf("error");
        return 0;
    }
    r_bytes=read(fd,buffer,6);
    if(r_bytes==-1){
        close(fd);
        printf("error");
        return 0;
    }
    buffer[5]='\0';
    write(STDOUT_FILENO,buffer,5);
    close(fd);
    return 0;

    
}