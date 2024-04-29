#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define file "myfifo"
int main(){
    mkfifo(file,0666);
  char message[100];
  int fd=open(file,O_WRONLY);
  if(fd<0){
    printf("error");
    return 0;
  }
  while(1){
    fgets(message,sizeof(message),stdin);
    write(fd,message,sizeof(message));
    if(strcmp(message,"exit\n")==0){
        break;
    }
    
  }
  close(fd);
  return 0;
}