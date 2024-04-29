//que 7.2:-Consider the bounded buffer problem consisting of5 producers and 10 consumers, and a buffer of size 10 items. Each producer performs 20 iterations. Every iteration a producer writes an item composed of 2 integer values (its ‘process id’ and the value of the iteration number) into the buffer. Each consumer performs 10 iterations. Every iteration, a consumer reads an item composed of 2 integer values from the buffer (the ‘process id’ of a producer and an iteration number), and then displays its own ‘process id’ followed by the 2 integers read from the buffer. 

//semaphore based
/*
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>
#define buffer_s 10
#define no_p 5
#define no_c 10
#define p_iter 20
#define c_iter 10
int buffer[buffer_s];
sem_t empty,full;
int in=0,out=0;
pthread_mutex_t mutex;
void * produce(void *arg){
    int id=*(int *)arg;
    for(int i=0;i<p_iter;i++){
        int item=(id<<16)|i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        in=(in+1)%buffer_s;
          printf("Producer %d produced item: %d %d\n", id, id, i);
          pthread_mutex_unlock(&mutex);
          sem_post(&full);
    }
    pthread_exit(0);
}
void *consume(void *arg){
    int id=*(int *)arg;
    for(int i=0;i<c_iter;i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item=buffer[out];
        out=(out+1)%buffer_s;
         pthread_mutex_unlock(&mutex);
         sem_post(&empty);
         printf("consumer %d consumed item: %d %d\n", id, item>>16,item & 0xFFFF);
    }
    pthread_exit(0);
}
int main(){
    pthread_t producer[no_p];
    pthread_t consumer[no_c];
    int pid[no_p];
    int cid[no_c];
    sem_init(&empty,0,buffer_s);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);
    for(int i=0;i<no_p;i++){
        pid[i]=i;
        pthread_create(&producer[i],NULL,produce,(void*)&pid[i]);
    }
    for(int i=0;i<no_c;i++){
        cid[i]=i;
        pthread_create(&consumer[i],NULL,consume,(void*)&cid[i]);
    }
    for(int i=0;i<no_p;i++){
        pthread_join(producer[i],NULL);
    }
    for(int i=0;i<no_c;i++){
       pthread_join(consumer[i],NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

   
}
*/
 
 //monitor based solution
 #include<stdio.h>
 #include<unistd.h>
 #include<stdlib.h>
 #include<pthread.h>
 #define buffer_s 10
 #define no_p 5
 #define no_c 10
 #define p_iter 20
 #define c_iter 10
  typedef struct{
    int pid;
    int iteration;
 }item;
 int in=0,out=0;
 item buffer[buffer_s];
 pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t buffer_not_full=PTHREAD_COND_INITIALIZER;
 pthread_cond_t buffer_not_empty=PTHREAD_COND_INITIALIZER;
 void insert_item(item temp){
    while((in+1)%buffer_s==out){
      pthread_cond_wait(&buffer_not_full,&mutex);
    }
    buffer[in]=temp;
    in=(in+1)%buffer_s;
    pthread_cond_signal(&buffer_not_empty);
 }
 item remove_item(){
    item temp;
    while(in==out){
        pthread_cond_wait(&buffer_not_empty,&mutex);
    }
    temp=buffer[out];
    out=(out+1)%buffer_s;
    pthread_cond_signal(&buffer_not_full);
    return temp;
 }
 void *produce(void* arg){
    int pid=*(int*)arg;
    for(int i=0;i<p_iter;i++){
        item temp;
        temp.pid=pid;
        temp.iteration=i;
        pthread_mutex_lock(&mutex);
        insert_item(temp);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
 }
 void *consume(void* arg){
    int pid=*(int*)arg;
    for(int i=0;i<p_iter;i++){
        pthread_mutex_lock(&mutex);
        item temp=remove_item();
        pthread_mutex_unlock(&mutex);
          printf("Consumer %d: Process ID: %d, Iteration: %d\n", pid, temp.pid, temp.iteration);
    }
    pthread_exit(NULL);
 }
 int main(){
    pthread_t producer[no_p],consumer[no_c];
    int pid[no_p],cid[no_c];
    for(int i=0;i<no_p;i++){
        pid[i]=i;
        pthread_create(&producer[i],NULL,produce,(void*)&pid[i]);
    }
    for(int i=0;i<no_p;i++){
        cid[i]=i;
        pthread_create(&consumer[i],NULL,consume,(void*)&cid[i]);
    }
    for(int i=0;i<no_p;i++){
        pthread_join(producer[i],NULL);
    }
     for(int i=0;i<no_c;i++){
        pthread_join(consumer[i],NULL);
    }
    pthread_mutex_destroy(&mutex);

 }