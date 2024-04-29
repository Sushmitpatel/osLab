//que5.1:-Write a  multithreaded program that calculates  various statistical values  for a list of numbers.  This  program will be passed a series of numbers on the command line and will then create three separate worker threads. One  thread  will  determine the  average  of the  numbers,  the  second  will  determine  the maximum  value,  and the third will determine the minimum value.For example, suppose your program is passed the integers: 90 81 78 95 79 72 85
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
struct pdata{
   int *members;
   int len;
};
int maximum,minimum;
void* calmin(void *arg){
    struct pdata* data=(struct pdata*)arg;
    int mn=data->members[0];
    for(int i=1;i<data->len;i++){
        if(data->members[i]<mn){
            mn=data->members[i];
        }
        printf("minimum\n");
    }
    minimum=mn;
    pthread_exit(0);
}
void* calmax(void *arg){
    struct pdata* data=(struct pdata*)arg;
    int mx=data->members[0];
    for(int i=1;i<data->len;i++){
        if(data->members[i]>mx){
            mx=data->members[i];
        }
         printf("maximum\n");
    }
    maximum=mx;
    pthread_exit(0);
}
int main(){
    pthread_t arr[2];
    int numbers[] = {90, 81, 78, 95, 79, 72, 85};
    int len = sizeof(numbers) / sizeof(numbers[0]);
    struct pdata data={numbers,len};
     int mxid=pthread_create(&arr[0],NULL,calmax,(void *)&data);
    int mid=pthread_create(&arr[0],NULL,calmin,(void *)&data);
    
     for(int i=0;i<2;i++){
        pthread_join(arr[i],NULL);
     }
     printf("min %d, max %d ",minimum,maximum);
}