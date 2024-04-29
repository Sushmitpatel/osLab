//que 6.1:-scheduling algorithms
#include<stdio.h>
#define n 4
struct p{
    int at;
    int bt;
    int tat;
    int wt;
    
    int ct;
    int priority;
    int completed;
};
void fcfs(struct p pr[]){
    int curr=0,complete=0;
    while(complete<n){
        int idx=-1,mn=1000;
        for(int i=0;i<n;i++){
            if(pr[i].at<=curr && pr[i].completed<=0){
               if(mn>pr[i].at){
                mn=pr[i].at;
                idx=i;
               }
            }
        }
        if(idx==-1){curr++;continue;}
         pr[idx].completed=1;
         pr[idx].ct=curr+ pr[idx].bt;
         pr[idx].tat= pr[idx].ct- pr[idx].at;
         pr[idx].wt= pr[idx].tat- pr[idx].bt;
        curr= pr[idx].ct;
        complete++;
    }
   for(int i=0;i<n;i++){
    printf("p%d completion time %d tat %d wt %d \n",i,pr[i].ct,pr[i].tat,pr[i].wt);
   }
}
void sjf(struct p pr[]){
    int curr=0,complete=0;
    while(complete<n){
        int idx=-1,mn=1000;
        for(int i=0;i<n;i++){
            if(pr[i].at<=curr && pr[i].completed<=0){
               if(pr[i].bt<mn){
                mn=pr[i].bt;
                idx=i;
               }
               else if(pr[i].bt==mn && pr[i].at<pr[idx].at){
                   idx=i;
               }
            }
        }
        if(idx==-1){curr++;continue;}
         pr[idx].completed=1;
         pr[idx].ct=curr+pr[idx].bt;
         pr[idx].tat= pr[idx].ct- pr[idx].at;
         pr[idx].wt= pr[idx].tat- pr[idx].bt;
         curr= pr[idx].ct;
        complete++;
    }
   for(int i=0;i<n;i++){
    printf("p%d completion time %d tat %d wt %d \n",i,pr[i].ct,pr[i].tat,pr[i].wt);
   }
}
void prs(struct p pr[]){
    int curr=0,complete=0;
    while(complete<n){
        int idx=-1,priority=0;
        for(int i=0;i<n;i++){
            if(pr[i].at<=curr && pr[i].completed<=0){
               if(priority<pr[i].priority){
                priority=pr[i].priority;
                idx=i;
               }
               else if(priority==pr[i].priority && pr[i].at<pr[idx].at){
                idx=i;
               }
            }
        }
        if(idx==-1){curr++;continue;}
        pr[idx].completed=1;
         pr[idx].ct=curr+pr[idx].bt;
         pr[idx].tat= pr[idx].ct- pr[idx].at;
         pr[idx].wt= pr[idx].tat- pr[idx].bt;
         curr= pr[idx].ct;
        complete++;
    }
   for(int i=0;i<n;i++){
    printf("p%d completion time %d tat %d wt %d \n",i,pr[i].ct,pr[i].tat,pr[i].wt);
   }
}
void rr(struct p pr[]){
    int curr=0,complete=0;
    int temp_bt[n];
    int temp_at[n];
    for(int i=0;i<n;i++){
        temp_bt[i]=pr[i].bt;
        temp_at[i]=pr[i].at;
    }
    while(complete<n){
        int idx=-1,mn=1000;
        for(int i=0;i<n;i++){
            if(temp_at[i]<=curr && pr[i].completed<=0){
               if(temp_at[i]<=mn){
                mn=temp_at[i];
                idx=i;
               }
            }
        }
        int temp=temp_bt[idx];
        temp_bt[idx]-=(temp_bt[idx]<2?temp_bt[idx]:2);
        if(idx==-1){curr++;continue;}
        if(temp_bt[idx]==0){
          pr[idx].completed=1;
          curr+=temp;
        pr[idx].ct=curr;
        pr[idx].tat=pr[idx].ct-pr[idx].at;
        pr[idx].wt=pr[idx].tat-pr[idx].bt;
         curr=pr[idx].ct;
        complete++;
        }
        else{
            curr+=2;
            temp_at[idx]+=2;
        }
        
    }
   for(int i=0;i<n;i++){
    printf("p%d completion time %d tat %d wt %d \n",i,pr[i].ct,pr[i].tat,pr[i].wt);
   }
}

int main(){
    
    struct p p1={0,24,0,0,0,2,0};
    struct p p2={2,3,0,0,0,4,0};
    struct p p3={1,3,0,0,0,3,0};
    struct p p4={3,7,0,0,0,1,0};
    struct p process[4]={p1,p2,p3,p4};
    printf("fcfs\n");
     fcfs(process);
    printf("\n");
    printf("sjf\n");
     struct p process1[4]={p1,p2,p3,p4};
     sjf(process1);
    printf("\n");
    printf("prs\n");
     struct p process2[4]={p1,p2,p3,p4};
    prs(process2);
    printf("\n");
    printf("rr\n");
     struct p process3[4]={p1,p2,p3,p4};
    rr(process3);
   
}