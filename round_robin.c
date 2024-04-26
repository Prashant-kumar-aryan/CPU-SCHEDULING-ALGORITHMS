#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int process_to_be_scheduled(int **arr, int n)
{
    int index, r = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (arr[i][5] && arr[i][6] <= r)
        {
            r = arr[i][6];
            index = i;
        }
    }

    return index;
}

int main()
{
    int n;
    printf("\nRound Robin Scheduling Algorithm\n\n");
    printf("Enter no. of processes : ");
    scanf("%d", &n);

    int i, j;

    int **arr = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        arr[i] = (int *)malloc(7 * sizeof(int));

    /*
    Process Pi
    arr[i][0] -> Arrival time
    arr[i][1] -> CPU burst time
    arr[i][2] -> Waiting time
    arr[i][3] -> Turn around time
    arr[i][4] -> Completion time
    arr[i][5] -> Remaining burst time
    arr[i][6] -> Ready queue
    */

    printf("Enter time slice : ");
    int slice;
    scanf("%d", &slice);

    printf("\nEnter arrival time & CPU burst time respectively :\n\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        scanf("%d %d", &arr[i][0], &arr[i][1]);
        arr[i][5] = arr[i][1];
        arr[i][6] = arr[i][0];
    }

    int count = 0;
    int curr = 0;
    int index;
    printf("\nGannt Chart---");
    while (count != n)
    {
        index = process_to_be_scheduled(arr, n);
        printf("P->%d (%d)", index, curr);
        if (curr < arr[index][0])
        {
            curr = arr[index][0];
        }
        if (slice >= arr[index][5])
        {
            curr += arr[index][5];
            arr[index][4] = curr;
            arr[index][3] = curr - arr[index][0];
            arr[index][2] = arr[index][3] - arr[index][1];
            count++;
            arr[index][5] = 0;
        }
        else
        {
            curr += slice;
            arr[index][5] -= slice;
            arr[index][6] = curr;
        }
    }
    printf("end->(%d)", curr);
    printf("\nProcess\tAT\tBT\tWT\tTAT\tCT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (j = 0; j < 5; j++)
            printf("%d\t", arr[i][j]);
        printf("\n");
    }
    // arr[i][3]->Turn around time
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (double)arr[i][3];
    }
    // arr[i][2] -> Waiting time
    printf("\nAverage TAT: %f ", sum / (double)n);
    sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (double)arr[i][2];
    }
    printf("\nAverage WT: %f ", sum / (double)n);

    // printGanttChart(n, arr[1], arr[4], arr[0]);
    return 0;
}
