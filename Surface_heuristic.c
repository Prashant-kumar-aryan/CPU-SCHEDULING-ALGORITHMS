#include <stdio.h>
#include <stdlib.h>

#define MAX_JOBS 100
#define MAX_MACHINES 100

// Function to calculate the suffrage value for a job
int calculateSuffrage(int processingTimes[MAX_JOBS][MAX_MACHINES], int jobIndex, int numMachines)
{
    int maxTime = -1;
    int secondMaxTime = -1;

    for (int i = 0; i < numMachines; i++)
    {
        if (processingTimes[jobIndex][i] > maxTime)
        {
            secondMaxTime = maxTime;
            maxTime = processingTimes[jobIndex][i];
        }
        else if (processingTimes[jobIndex][i] > secondMaxTime)
        {
            secondMaxTime = processingTimes[jobIndex][i];
        }
    }

    return maxTime - secondMaxTime;
}

void suffrageHeuristic(int processingTimes[MAX_JOBS][MAX_MACHINES], int numJobs, int numMachines)
{
    int jobOrder[MAX_JOBS];
    int jobCompleted[MAX_JOBS] = {0};

    int suffrageValues[MAX_JOBS];
    for (int i = 0; i < numJobs; i++)
    {
        suffrageValues[i] = calculateSuffrage(processingTimes, i, numMachines);
    }

    for (int k = 0; k < numJobs; k++)
    {
        int maxSuffrage = -1;
        int selectedJob = -1;

        // Find the job with the highest suffrage value
        for (int i = 0; i < numJobs; i++)
        {
            if (!jobCompleted[i] && suffrageValues[i] > maxSuffrage)
            {
                maxSuffrage = suffrageValues[i];
                selectedJob = i;
            }
        }
        int nextMachine = 0;
        while (processingTimes[selectedJob][nextMachine] == -1)
        {
            nextMachine++;
        }

        jobOrder[k] = selectedJob;
        jobCompleted[selectedJob] = 1;

        for (int i = 0; i < numJobs; i++)
        {
            if (!jobCompleted[i])
            {
                suffrageValues[i] = calculateSuffrage(processingTimes, i, numMachines);
            }
        }
    }

    printf("Job order after Suffrage Heuristic:\n");
    for (int i = 0; i < numJobs; i++)
    {
        printf("Job %d ", jobOrder[i] + 1);
    }
    printf("\n");
}

int main()
{
    int numJobs, numMachines;
    int processingTimes[MAX_JOBS][MAX_MACHINES];

    printf("Enter the number of jobs: ");
    scanf("%d", &numJobs);

    printf("Enter the number of machines: ");
    scanf("%d", &numMachines);

    printf("Enter the processing times for each job and machine:\n");
    for (int i = 0; i < numJobs; i++)
    {
        for (int j = 0; j < numMachines; j++)
        {
            scanf("%d", &processingTimes[i][j]);
        }
    }

    suffrageHeuristic(processingTimes, numJobs, numMachines);

    return 0;
}