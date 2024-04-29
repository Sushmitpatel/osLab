#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#define file "myfifo"
int main(){
  char message[100];
  int fd=open(file,O_RDONLY);
  if(fd<0){
    printf("error");
    return 0;
  }
  while(1){
    read(fd,message,sizeof(message));
    if(strcmp(message,"exit\n")==0){
        break;
    }
    printf("%s\n",message);
  }
  close(fd);
  return 0;
}