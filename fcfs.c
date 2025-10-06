// #include <stdio.h>

// void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
//     wt[0] = 0;  // Waiting time for the first process is 0
//     for (int i = 1; i < n; i++) {
//         wt[i] = at[i - 1] + wt[i - 1] + bt[i - 1] - at[i];
//     }
// }

// void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int at[], int tat[]) {
//     for (int i = 0; i < n; i++) {
//         tat[i] = wt[i] + bt[i];
//     }
// }

// void findAvgTime(int processes[], int n, int bt[], int at[]) {
//     int wt[n], tat[n], total_wt = 0, total_tat = 0;
//     findWaitingTime(processes, n, bt, wt, at);
//     findTurnAroundTime(processes, n, bt, wt, at, tat);

//     printf("Processes\tArrival time\tBurst time\tWaiting time\tTurnaround time\n");
//     for (int i = 0; i < n; i++) {
//         total_wt += wt[i];
//         total_tat += tat[i];
//         printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
//     }

//     printf("Average waiting time = %.2f\n", (float)total_wt / n);
//     printf("Average turnaround time = %.2f\n", (float)total_tat / n);

//     // Print Gantt chart
//     printf("\nGantt Chart: \n");
//     int time = 0;
//     printf("|");
//     for (int i = 0; i < n; i++) {
//         // We simulate the process execution by adding burst time to the current time
//         printf("P%d\t|", processes[i]);
//         time += bt[i];
//     }
//     printf("\n");

//     // Print timeline below the Gantt chart
//     time = 0;
//     printf("0\t");
//     for (int i = 0; i < n; i++) {
//         time += bt[i];
//         printf("%d\t", time);
//     }
//     printf("\n");
// }

// int main() {
//     int processes[] = {1, 2, 3, 4, 5};  // Process IDs
//     int n = sizeof(processes) / sizeof(processes[0]);
//     int burst_time[] = {8, 1, 3, 2, 6};  // Burst times for each process
//     int arrival_time[] = {0, 1, 2, 3, 4};  // Arrival times for each process

//     findAvgTime(processes, n, burst_time, arrival_time);

//     return 0;
// }



#include <stdio.h>

// Function to calculate Waiting Time
void findWaitingTime(int n, int bt[], int wt[], int at[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        int service_time = at[i - 1] + wt[i - 1] + bt[i - 1];
        wt[i] = service_time - at[i];
        if (wt[i] < 0) wt[i] = 0;
    }
}

// Function to calculate Turnaround Time
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to perform FCFS Scheduling and print everything
void findAvgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n];
    float total_wt = 0, total_tat = 0;

    findWaitingTime(n, bt, wt, at);
    findTurnAroundTime(n, bt, wt, tat);

    printf("\nProcesses\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] > current_time) {
            current_time = at[i]; // CPU idle until process arrives
        }
        printf(" P%d |", processes[i]);
        current_time += bt[i];
    }

    printf("\n0");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] > current_time) {
            current_time = at[i];
        }
        current_time += bt[i];
        printf("\t%d", current_time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], at[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    findAvgTime(processes, n, bt, at);

    return 0;
}
