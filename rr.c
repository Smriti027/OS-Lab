#include<stdio.h>
#include<limits.h>
#include<stdbool.h> 
#include <stdlib.h> 

struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,start_time;
  int bt_remaining;
}ps[100];


int findmax(int a, int b)
{
    return a>b?a:b;
}

int comparatorAT(const void * a, const void *b)
{
   int x =((struct process_struct *)a) -> at;
   int y =((struct process_struct *)b) -> at;
   if(x<y)
     return -1;  
   else if( x>=y) 
    return 1;    
}

int comparatorPID(const void * a, const void *b)
{
   int x =((struct process_struct *)a) -> pid;
   int y =((struct process_struct *)b) -> pid;
   if(x<y)
     return -1;  
   else if( x>=y)
    return 1;    
}

int main()
{
    
    int n,index;
    bool visited[100]={false},is_first_process=true;
    int current_time = 0,max_completion_time;
    int completed = 0,tq, total_idle_time=0,length_cycle;    
    int queue[100],front=-1,rear=-1;
    float sum_tat=0,sum_wt=0,sum_rt=0;
   

    printf("Enter the no. of processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
    	printf("\nEnter process %d arrival time: ",i+1);
    	scanf("%d",&ps[i].at);
    	ps[i].pid=i;
    	printf("\nEnter process %d burst time: ",i+1);
    	scanf("%d",&ps[i].bt);
    	ps[i].bt_remaining=ps[i].bt;
    }
    printf("\nEnter time quanta: ");
    scanf("%d",&tq);
    qsort((void *)ps,n, sizeof(struct process_struct),comparatorAT);
    front=rear=0;
    queue[rear]=0;    
    visited[0] = true;
   
    while(completed != n) 
    {
      index = queue[front];      
      front++;
      
      if(ps[index].bt_remaining == ps[index].bt)
      {
            ps[index].start_time = findmax(current_time,ps[index].at);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
            current_time =  ps[index].start_time;
            is_first_process = false;
             
      }

      if(ps[index].bt_remaining-tq > 0)
      {    
            ps[index].bt_remaining -= tq;
            current_time += tq;
      }
      else 
      {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
             
      }
      for(int i = 1; i < n; i++) 
      {
          if(ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false) 
          {
            queue[++rear]=i;
            visited[i] = true;
          }
      }
      if( ps[index].bt_remaining> 0) 
       
          queue[++rear]=index;
    
      if(front>rear)
      {
          for(int i = 1; i < n; i++)
          {
            if(ps[i].bt_remaining > 0)
            {
              queue[rear++]=i;
              visited[i] = true;
              break;
            }
          }
      }
   } 
	ps[n-1].ct=ps[n-1].ct-tq;
	ps[n-1].tat=ps[n-1].tat-tq;
	ps[n-1].wt=ps[n-1].wt-tq;
	ps[n-1].rt=ps[n-1].rt-tq;
	 
  qsort((void *)ps,n, sizeof(struct process_struct),comparatorPID);
  
  printf("\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
  for(int i=0;i<n;i++)
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,ps[i].at,ps[i].bt,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt);
  printf("\n");    

  printf("\nAverage Turn Around time= %.2f",((float)sum_tat-tq)/n);
  printf("\nAverage Waiting Time= %.2f",((float)sum_wt-tq)/n);
  printf("\nAverage RT= %.2f\n",((float)sum_rt-tq)/n);  
  return 0;
}


