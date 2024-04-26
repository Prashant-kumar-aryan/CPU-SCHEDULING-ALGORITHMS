#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void endt(int n, int bursttime[], int endtime[], int AT[])
{
    endtime[0] = bursttime[0] + AT[0];
    for (int i = 1; i < n; i++)
    {
        if (endtime[i - 1] >= AT[i])
            endtime[i] = bursttime[i] + endtime[i - 1];
        else
            endtime[i] = bursttime[i] + AT[i];
    }
}
void endnew(int n, int bursttime[], int endtime[], int AT[], char gantt[])
{
    endtime[0] = bursttime[0] + AT[0];
    sprintf(gantt, "P1(%d)", endtime[0]);
    for (int i = 1; i < n; i++)
    {
        if (endtime[i - 1] >= AT[i])
        {
            endtime[i] = bursttime[i] + endtime[i - 1];
            sprintf(gantt + strlen(gantt), " -> P%d(%d)", i + 1, endtime[i]);
        }
        else
        {
            endtime[i] = bursttime[i] + AT[i];
            sprintf(gantt + strlen(gantt), " -> Idle(%d) -> P%d(%d)", endtime[i - 1], i + 1, endtime[i]);
        }
    }
}
void printGanttChart(int n, int bursttime[], int endtime[], int AT[])
{
    char gantt[1000]; // Adjust the size according to your needs
    endnew(n, bursttime, endtime, AT, gantt);

    printf("\nGantt Chart:\n");
    printf("%s\n", gantt);
}
void turnaroundtime(int n, int TAT[], int endtime[], int AT[])
{
    for (int i = 0; i < n; i++)
    {
        TAT[i] = endtime[i] - AT[i];
    }
}
void waitingtime(int n, int WT[], int TAT[], int bursttime[])
{
    for (int i = 0; i < n; i++)
    {
        WT[i] = TAT[i] - bursttime[i];
    }
}
void responsetime(int n, int RT[], int AT[], int endtime[])
{
    RT[0] = 0;
    for (int i = 1; i < n; i++)
    {
        RT[i] = endtime[i - 1] + (AT[i] - endtime[i - 1]) - AT[i];
    }
}
struct input
{
    int at;
    int bt;
};

void swap(struct input *xp, struct input *yp)
{
    struct input temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main()
{
    int n;
    printf("Enter the no of process:");
    scanf("%d", &n);
    struct input arr[n];

    printf("\nEnter the arrival time for All the process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i].at);
    }
    printf("\nEnter the burst time for ALl the  process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i].bt);
    }
    arrange(arr, n);
    int AT[n], bursttime[n];
    for (int i = 0; i < n; i++)
    {
        AT[i] = arr[i].at;
        bursttime[i] = arr[i].bt;
    }
    int endtime[n], TAT[n], WT[n], RT[n];

    endt(n, bursttime, endtime, AT);
    turnaroundtime(n, TAT, endtime, AT);
    waitingtime(n, WT, TAT, bursttime);
    responsetime(n, RT, AT, endtime);
    printf("\nProcesses AT Burst time End time TAT Waiting Time Response Time :\n");

    for (int i = 0; i < n; i++)
    {
        printf(" %d ", (i + 1));
        printf("	  %d ", AT[i]);
        printf("	 %d", bursttime[i]);
        printf("	 %d", endtime[i]);
        printf("	  %d", TAT[i]);
        printf("	 %d", WT[i]);
        printf("	    %d\n", RT[i]);
    }
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (double)TAT[i];
    }
    printf("\nAverage TAT: %f ", sum / (double)n);
    sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (double)WT[i];
    }
    printf("\nAverage WT: %f ", sum / (double)n);
    printGanttChart(n, bursttime, endtime, AT);
    return 0;
}

void arrange(struct input arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].at > arr[j + 1].at)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}