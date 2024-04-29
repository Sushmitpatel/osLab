//que 5.2:-Write  a  program  to  create  two  matrices,  A  and  B, of  sizes  40x40,  which  only  take  binary  inputs  0  and  1. Create  two threads running parallel where  one thread will compute  the  summation of the two matrices and the  other  will  compute  their  difference.  There  will  be one  main thread  which  will  wait for  the  two  parallel threads to  complete  their  task  and  it  will compute  the  multiplication  of the  two  previously  obtained  output and print the final output.
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define n 2
int A[n][n],B[n][n],sum[n][n],diff[n][n],mul[n][n];
void *add(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            sum[i][j]=A[i][j]+B[i][j];
        }
    }
    pthread_exit(0);
}
void *sub(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            diff[i][j]=A[i][j]-B[i][j];
        }
    }
    pthread_exit(0);
}
int main(){
    pthread_t arr[2];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&B[i][j]);
        }
    }
    pthread_create(&arr[0],NULL,add,NULL);
    pthread_create(&arr[1],NULL,sub,NULL);
    pthread_join(arr[0],NULL);
    pthread_join(arr[1],NULL);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                mul[i][k]+=sum[i][j]*diff[j][k];
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",mul[i][j]);
        }
        printf("\n");
    }
}