#include<stdio.h>

// max no of processes and resources
#define P 5
#define R 3

void print(int m[][R])
{
    for(int i=0;i<P;i++)
    {
    for(int j=0;j<R;j++)
        printf("%d-",m[i][j]);
    printf("\n");
    }
}
// Function to check if the requested resources can be allocated to the process safely
int isSafe(int processes[], int available[], int max[][R], int allot[][R]) {
    int need[P][R];
    int finish[P] = {0}; // Initialize finish array to track whether a process has finished
    // Calculate need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
    
    printf("Resource need\n");
    print(need);
    int work[R];
    
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
        
    }

    int count = 0;
    while (count < P) 
    {
        int found = 0; // Flag to check if a process can be allocated resources in this iteration
        for (int i = 0; i < P; i++) 
        {
            if (finish[i] == 0) 
            {
                int j,flag=1;
                for (j = 0; j < R; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        flag=0;break;
                    }
                }
                if (flag == 1) 
                {
                    // Process can be allocated resources
                    printf("Available Resources");
                    for (int k = 0; k < R; k++)
                        {printf("-%d",work[k]);}
                        
                        printf("\nprocess-p%d can be allocated resources",i);
                    for (int k = 0; k < R; k++)
                        {printf("-%d",need[i][k]);}
                    for (int k = 0; k < R; k++) 
                    {
                        work[k] += allot[i][k];
                    }
                    printf("\n");
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0) 
        {
            // If no process can be allocated resources, the system is not in a safe state
            return 0;
        }
    }
    // If all processes are allocated resources safely, the system is in a safe state
    return 1;
}

// Banker's Algorithm function to allocate resources to processes
void bankerAlgorithm(int processes[], int available[], int max[][R], int allot[][R]) {
    if (isSafe(processes, available, max, allot)) {
        printf("Safe state, allocating resources...\n");
        // Allocate resources to processes (for example)
        // Your code to allocate resources goes here
    } else {
        printf("Unsafe state, cannot allocate resources. Possible deadlock.\n");
    }
}

void main() {
    int processes[] = {0, 1, 2, 3, 4}; // Process IDs
    int available[] = {3, 3, 2}; // Available instances of resources
    // Maximum resource needs of processes
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    // Resources currently allocated to processes
    int allot[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    printf("Max Requirement\n");
    print(max);
    printf("Resource Allotment\n");
    print(allot);
    bankerAlgorithm(processes, available, max, allot);
}