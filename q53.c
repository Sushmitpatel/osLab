//que 5.3:-Write  a  program  that  receives  an  arbitrary  number  of  integers  as  arguments.  LetNbe  the  number  of arguments provided by the user. The program createsNthreads, each of which is assigned an IDi, with0 < i <=  N.  Theiththread  computes aprefix  productof  all  numbers  up to  and  including  theithargument, i.e.  the first thread returns the first number, the second thread computes the product of the first and second number, and  so  on.The  main  thread  then  waits  for  all  threads  to  complete  and  prints  their  resultin  orderin  the format"product <i> = <product>".
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
int* input;
int *output;
void * product(void *arg){
    int n=*(int *)arg;
    int temp=1;
    for(int i=0;i<n;i++){
        temp*=input[i];
    }
    output[n-1]=temp;
    pthread_exit(0);
}
int main(){
    int n;
    scanf("%d",&n);
    input=(int *)malloc(n*sizeof(int));
    output=(int *)malloc(n*sizeof(int));
    int arr[n];
    pthread_t p[n];
    for(int i=0;i<n;i++){
        scanf("%d",&input[i]);
        arr[i]=i+1;
        p[i]=i+1;
    }
    for(int i=0;i<n;i++){
        pthread_create(&p[i],NULL,product,(void*)&arr[i]);
    }
    for(int i=0;i<n;i++){
        pthread_join(p[i],NULL);
    }
    for(int i=0;i<n;i++){
        printf("%d ",output[i]);
    }
}