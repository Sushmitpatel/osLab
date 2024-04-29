// Que3:- Write a program to read all txt files (that is files that ends with .txt) in the current directory and merge them all to one txt file and returns a file descriptor for the new file
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
int merged(const char *outputFileName){
DIR *dir;
ssize_t rd_bytes,wr_bytes;
struct dirent *entry;
char buffer[1024];
int m_fd;
dir=opendir(".");
if(dir==NULL){
    printf("error in opening dir");
    return -1;
}
m_fd=open(outputFileName,O_WRONLY| O_CREAT,0644);
if(m_fd==-1){
    printf("error in opening merged.txt");
    closedir(dir);
    return -1;
}
while((entry=readdir(dir))!=NULL){
    if(strcmp(strrchr(entry->d_name,'.'),".txt")==0){
        int fd=open(entry->d_name,O_RDONLY);
        if(fd==-1){
            printf("error in opening");
            continue;
        }
        if(rd_bytes=read(fd,buffer,1024)){
            wr_bytes=write(m_fd,buffer,rd_bytes);
            if(wr_bytes==-1){
                printf("error in writing output file");
                close(fd);
                closedir(dir);
                close(m_fd);
                return -1;
            }
        }
        close(fd);
    }
}
close(m_fd);
closedir(dir);
return m_fd;

}
int main(){
 int m_fd=merged("merged.txt");
 if(m_fd!=-1){
    printf("successfull");
 }
 else{
    printf("error");
 }
 return 0;
}