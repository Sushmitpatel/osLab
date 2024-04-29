//que 7.2:-Write a program where a parent process creates a shared memory and writes 1000 in a variable in the shared memory before creating 2 children processes A and B. After that, the parent waits for children termination and destroys the shared memory segment. Each child process performs 5 iterations. Every iteration process A adds 200 to the shared variable, and process B adds 100 to the shared variable. To help race conditions appear, both processes sleep for a random amount of time between the time they read the shared variable and the time they write back the shared variable after modification.              A. Could you predict the output of the program before execution? Explain your answer.                           b.  Adjust the sleeping duration of one process (or both processes) to have a different output. Could you predict this output? Explain your answer. 
/* Ans:-a. Predicting the output of the program before execution can be challenging due to the race conditions introduced by the concurrent access and modification of the shared variable by the two child processes. However, we can make some observations:

The initial value of the shared variable is set to 1000 by the parent process.
Process A adds 200 to the shared variable in each iteration.
Process B adds 100 to the shared variable in each iteration.
Both processes sleep for a random amount of time between reading and writing the shared variable.
Given these observations, the final value of the shared variable will depend on the timing and order of execution of the two child processes. Since the order of execution and sleep durations are random, it's difficult to predict the exact output. However, we can expect that the final value of the shared variable will be greater than 1000 due to the additions made by both processes.

b. Adjusting the sleeping duration of one or both processes will change the timing of their access and modification of the shared variable. If one process sleeps for a longer duration compared to the other, it may have a delayed update to the shared variable, allowing the other process to update it first. This can lead to a different final value of the shared variable.

For example, if we increase the sleeping duration of process B, it might result in process A updating the shared variable multiple times before process B updates it, resulting in a larger final value. Conversely, if we decrease the sleeping duration of process B, it might update the shared variable more frequently, resulting in a smaller final value compared to process A.

Overall, predicting the exact output of the program with different sleeping durations is still challenging due to the unpredictable nature of concurrent execution and race conditions.

*/

#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<stdlib.h>
#define size 1024
int main(){
    int shmid,pida,pidb;
    int *shared_memory;
    shmid=shmget(2432,size,IPC_CREAT|0666);
    shared_memory=shmat(shmid,NULL,0);
    *shared_memory=1000;
    if((pida=fork())==0){
     //child Process A
     for(int i=0;i<5;i++){
        int random=(2+rand()%5);
        sleep(random);
        *shared_memory+=200;
        printf("pa added 200 in %d th iteration is %d\n",i,*shared_memory);
     
     }
     exit(0);
    }
    if((pidb=fork())==0){
     //child Process A
     for(int i=0;i<5;i++){
        int random=(4+rand()%5);
        sleep(random);
        *shared_memory+=100;
        printf("pB added 100 in %d th iteration is %d\n",i,*shared_memory);
     }
     exit(0);
    }
    waitpid(pida,NULL,0);
    waitpid(pidb,NULL,0);
    printf("final value: %d",*shared_memory);
    shmdt(shared_memory);
}
