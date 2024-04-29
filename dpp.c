#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define n 5
#define hungry 1
#define eating 2
#define thinking 0
#define left(philosopher) (philosopher+4)%n
#define right(philosopher) (philosopher+1)%n
int state[n];
sem_t forks[n];
sem_t mutex;
void test(int num){
if(state[num]==hungry && state[left(num)]!=eating && state[right(num)]!=eating){
    state[num]=eating;
    sem_post(&forks[num]);
}
}
void take_fork(int num){
 sem_wait(&mutex);
 state[num]=hungry;
 test(num);
 sem_post(&mutex);
 sem_wait(&forks[num]);
}

void put_fork(int num){
 sem_wait(&mutex);
 state[num]=thinking;
 test(left(num));
 test(right(num));
 sem_post(&mutex);

}
void *pf(void *arg){
    int num=*(int *)arg;
    for(int i=0;i<10;i++){
        //thinking
        printf("pf is hungry\n");
        take_fork(num);
        printf("pf is eating\n");
        put_fork(num);
        printf("pf is thinking\n");

    }
}

int main(){
    pthread_t arr[n];
    int id[n];
    sem_init(&mutex,0,1);
    for(int i=0;i<n;i++){
        sem_init(&forks[i],0,0);
    }
    for(int i=0;i<n;i++){
        id[i]=i;
        pthread_create(&arr[i],NULL,pf,(void*)&id[i]);
    }
    for(int i=0;i<n;i++){
        pthread_join(arr[i],NULL);
    }
    for(int i=0;i<n;i++){
        sem_destroy(&forks[i]);
    }
}

