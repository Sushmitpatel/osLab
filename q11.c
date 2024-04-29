//que 1:-Write a program to read a maximum of 15 characters from the user and print them on the screen. 
#include<stdio.h>
#include<unistd.h>
int main(){
    char input[16];
    int bytesize;
    bytesize=read(0,input,sizeof(input)-1);
    if(bytesize==-1){
        printf("some error occured\n");
        return 0;
    }
    input[bytesize]='\0';
    write(1,input,sizeof(input)-1);
    printf("\n");
    return 0;
}