//Que4.3:-Implement  a  system  that  consists  of  two  processes;  parent  and  child, communicates  via  Named  pipe.  The  parent requeststhe  user  to  enter  a sentence,  then  it  will  write  this  sentence  into  the  pipe.  The  child  reads  this sentence,  count  the  number  of  vowel  letters  in  it,  print  the  sentence  on  the screen and the number of vowels letters in it.The output will be something like this                   Parent process: Please enter a sentence: Welcome to OS lab                                                   Parent process: Write the sentence into the pipe.      Child process: Read Welcome to OS lab, number of vowels =6
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#define file "my"
int count_vowels(char *sentence) {
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == 'a' || sentence[i] == 'e' || sentence[i] == 'i' || sentence[i] == 'o' || sentence[i] == 'u' ||
            sentence[i] == 'A' || sentence[i] == 'E' || sentence[i] == 'I' || sentence[i] == 'O' || sentence[i] == 'U') {
            count++;
        }
    }
    return count;
}
int main(){
   mkfifo(file,0666);
  
  
   int pid=fork();
   if(pid<0){
    printf("error");
    return 0;
   }
   if(pid){
     int fd=open(file,O_WRONLY);
      if(fd<0){
    printf("error");
    return 0;
   }
     char sentence[100];
     printf("enter\n");
    fgets(sentence,sizeof(sentence),stdin);
    write(fd,sentence,sizeof(sentence));
    close(fd);

   }
   else{
   int fd=open(file,O_RDONLY);
   if(fd<0){
    printf("error");
    return 0;
   }
   char sentence[100];
   read(fd,sentence,sizeof(sentence));
   int cnt=count_vowels(sentence);
   printf("%d",cnt);
   close(fd);

   }
   return 0;
}