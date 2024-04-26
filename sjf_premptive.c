 #include <stdio.h>
#include<stdlib.h>
#include<limits.h>

void endt(int n,int AT[],int bursttime[],int endtime[],int firstcpu[],int order[])
{
  
    int *flag = (int*)calloc(n, sizeof(int));int g=0;
    int p=0;//for order of completion
    int currtime=0;//keeps record of the current time
    int nop=n;//total no of processes 
    int check=0;//to check if any process is in the ready queue or not
    
    int *first= (int*)calloc(n, sizeof(int));
    int burst_finish[n];
    for(int i=0;i<n;i++)
        burst_finish[i]=bursttime[i];


    printf("\nOrder of execution in per sec :");

    while(nop)
    {
    
        for(int j=0;j<n;j++)//to check how many processes have arrived 
        {
        if(AT[j]<=currtime&&flag[j]!=-1){
        flag[j]=1;

        check=1;
        }
    }
    int min_bt=INT_MAX,min_bt_index;
    for(int i=0;i<n;i++)//to find the min burst time among all the processes arrived 
    {
        if(flag[i]==1&&burst_finish[i]<min_bt)
        {
            min_bt=burst_finish[i];
            min_bt_index=i;
        }
    }
    if(check==1)
    {
        if(first[min_bt_index]==0)
        {
            firstcpu[min_bt_index]=currtime;
            first[min_bt_index]=-1;
        }
            printf("p%d  ",(min_bt_index+1));
            endtime[min_bt_index]=(currtime+1);
            burst_finish[min_bt_index]=(burst_finish[min_bt_index]-1);
            if(burst_finish[min_bt_index]==0)
            {
                flag[min_bt_index]=-1;
                --nop;
            }
            currtime=endtime[min_bt_index];
    }
    else if(check==0)//in case no process has arrived and the cpu is idle
    {
        int min_at=INT_MAX;
        for(int j=0;j<n;j++)
        {
            if(AT[j]>currtime&&flag[j]!=-1&&AT[j]<min_at)
            min_at=AT[j];
        }
        currtime=min_at;
    }
    }
}

void turnaroundtime(int n,int TAT[],int endtime[],int AT[])
{
    for(int i=0;i<n;i++){
        TAT[i]=endtime[i]-AT[i];
    }
}
void waitingtime(int n,int WT[],int TAT[],int bursttime[])
{
    for(int i=0;i<n;i++){
        WT[i]=TAT[i]-bursttime[i];
    }
}
void responsetime(int n,int RT[],int AT[],int firstcpu[])
{
    for(int i=0;i<n;i++){
        RT[i]=firstcpu[i]-AT[i];
    }
}


int main()
{
    int n;
    printf("Enter the no of process:");
    scanf("%d",&n);
    int AT[n],bursttime[n];
    for(int i=0;i<n;i++){
    printf("\nEnter the arrival time for %d process: ",i+1);
    scanf("%d",&AT[i]);
    printf("\nEnter the burst time for %d process: ",i+1);
    scanf("%d",&bursttime[i]);
    }

    int endtime[n],TAT[n],WT[n],RT[n],firstcpu[n],order[n];
    endt(n,AT,bursttime,endtime,firstcpu,order);
    turnaroundtime(n,TAT,endtime,AT);
    waitingtime(n,WT,TAT,bursttime); 
     responsetime(n,RT,AT,firstcpu);
     printf("\n");
  

    printf("\nProcesses AT Burst time End time TAT Waiting Time Response Time:\n");

	for(int i=0; i<n; i++)
	{
		printf(" %d ",(i+1));
		printf("	  %d ",AT[i] );
		printf("	 %d",bursttime[i] );
		printf("	 %d",endtime[i] );
        printf("	  %d",TAT[i] );
		printf("	 %d",WT[i] );
        printf("	   %d\n",RT[i] );
	}
    
    return 0;
}