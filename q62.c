#include<stdio.h>
#define n 5
struct p{
    int at;
    int bt;
    int tat;
    int wt;
    
    int ct;
    int priority;
    int completed;
};
void srtf(struct p pr[]){
    int temp_bt[n];
    for(int i=0;i<n;i++){
        temp_bt[i]=pr[i].bt;
    }
    int curr=0,complete=0;
    while(complete<n){
        int idx=-1,mn=1000;
        for(int i=0;i<n;i++){
            if(pr[i].at<=curr && pr[i].completed<=0){
               if(mn>temp_bt[i]){
                mn=pr[i].at;
                idx=i;
               }
               else if(mn==temp_bt[i] && pr[i].at<pr[idx].at){
                idx=i;
               }
            }
        }
        if(idx==-1){curr++;continue;}
        temp_bt[idx]-=1;
        curr++;
        if(temp_bt[idx]==0){
          pr[idx].completed=1;
         pr[idx].ct=curr;
         pr[idx].tat= pr[idx].ct- pr[idx].at;
         pr[idx].wt= pr[idx].tat- pr[idx].bt;
        curr= pr[idx].ct;
        complete++;
        }
         
    }
   for(int i=0;i<n;i++){
    printf("p%d completion time %d tat %d wt %d \n",i,pr[i].ct,pr[i].tat,pr[i].wt);
   }
}
int main(){
    
    struct p p1={3,4,0,0,0,0,0};
    struct p p2={1,2,0,0,0,0,0};
    struct p p3={4,1,0,0,0,0,0};
    struct p p4={2,6,0,0,0,0,0};
    struct p p5={5,2,0,0,0,0,0};
    struct p process[5]={p1,p2,p3,p4,p5};
    srtf(process);
   
}