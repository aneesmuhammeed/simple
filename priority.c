// #include <stdio.h>

// struct Process {
//     int processNo;
//     int arrivalTime;
//     int burstTime;
//     int priority;
// };

// // Sort processes based on arrival time and priority
// void sortProcesses(struct Process proc[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = i + 1; j < n; j++) {
//             if (proc[j].arrivalTime < proc[i].arrivalTime ||
//                 (proc[j].arrivalTime == proc[i].arrivalTime && proc[j].priority < proc[i].priority)) {
//                 // Swap processes
//                 struct Process temp = proc[i];
//                 proc[i] = proc[j];
//                 proc[j] = temp;
//             }
//         }
//     }
// }

// // Calculate waiting time
// void calculateWaitingTime(struct Process proc[], int wt[], int n) {
//     wt[0] = 0; // Waiting time for the first process is zero
//     int pstart[n];
//     pstart[0] = 0;
//     for (int i = 1; i < n; i++) {
//         pstart[i] = pstart[i - 1] + proc[i - 1].burstTime;
//         wt[i] = pstart[i] - proc[i].arrivalTime;
//     }
// }

// // Calculate turnaround time
// void calculateTurnaroundTime(struct Process proc[], int wt[], int tat[], int n) {
//     for (int i = 0; i < n; i++) {
//         tat[i] = proc[i].burstTime + wt[i];
//     }
// }

// // Function to print Gantt chart
// void printGanttChart(struct Process proc[], int n, int wt[], int tat[]) {
//     int total_time = 0;
//     printf("\nGantt Chart:\n");
//     printf("|");
//     for (int i = 0; i < n; i++) {
//         printf("P%d\t|", proc[i].processNo);
//     }
//     printf("\n");

//     printf("0");
//     for (int i = 0; i < n; i++) {
//         total_time += proc[i].burstTime;
//         printf("\t%d", total_time);
//     }
//     printf("\n");
// }

// int main() {
//     int n;
//     printf("Enter the number of processes: ");
//     scanf("%d", &n);

//     struct Process proc[n];
//     int wt[n], tat[n];

//     printf("Enter process details (arrival time, burst time, priority):\n");
//     for (int i = 0; i < n; i++) {
//         proc[i].processNo = i + 1;
//         printf("P%d: ", i + 1);
//         scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
//     }

//     // Sort processes based on arrival time and priority
//     sortProcesses(proc, n);

//     // Calculate waiting time and turnaround time
//     calculateWaitingTime(proc, wt, n);
//     calculateTurnaroundTime(proc, wt, tat, n);

//     // Display results
//     float awt = 0, atat = 0;
//     printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
//     for (int i = 0; i < n; i++) {
//         printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].processNo, proc[i].arrivalTime,
//                proc[i].burstTime, proc[i].priority, wt[i], tat[i]);
//         awt += wt[i];
//         atat += tat[i];
//     }
    
//     printf("AWT=%.2f\t ATAT=%.2f\n", awt / n, atat / n);

//     // Print the Gantt chart
//     printGanttChart(proc, n, wt, tat);

//     return 0;
// }



#include <stdio.h>

typedef struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;
    int st; // start time for Gantt chart
} Process;

typedef struct GanttBlock {
    int pid;
    int start;
    int end;
} GanttBlock;

void main() {
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    Process procs[n];
    GanttBlock gantt[n];  // To store execution order
    int gIndex = 0;

    printf("Enter process details\n");
    for (int i = 0; i < n; i++) {
        procs[i].pid = i + 1;
        printf("Arrival time of P%d: ", i + 1);
        scanf("%d", &procs[i].at);
        printf("Burst time of P%d: ", i + 1);
        scanf("%d", &procs[i].bt);
        printf("Priority of P%d: ", i + 1);
        scanf("%d", &procs[i].priority);
        procs[i].tat = -1;
        procs[i].wt = -1;
        procs[i].ct = -1;
        procs[i].st = -1;
    }

    int cur_time = 0, count = 0;

    while (count < n) {
        int high_prt_index = -1;
        int high_prt = 9999;
        for (int i = 0; i < n; i++) {
            if (procs[i].at <= cur_time && procs[i].ct == -1) {
                if (procs[i].priority < high_prt) {
                    high_prt = procs[i].priority;
                    high_prt_index = i;
                }
            }
        }

        if (high_prt_index == -1) {
            cur_time++;
        } else {
            procs[high_prt_index].st = cur_time;
            cur_time += procs[high_prt_index].bt;
            procs[high_prt_index].ct = cur_time;
            procs[high_prt_index].tat = cur_time - procs[high_prt_index].at;
            procs[high_prt_index].wt = procs[high_prt_index].tat - procs[high_prt_index].bt;

            gantt[gIndex].pid = procs[high_prt_index].pid;
            gantt[gIndex].start = procs[high_prt_index].st;
            gantt[gIndex].end = procs[high_prt_index].ct;
            gIndex++;

            count++;
        }
    }

    float tot_wt = 0.0, tot_tat = 0.0;

    printf("\nProcesses\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t\t%d\t%d\n",
               procs[i].pid, procs[i].at, procs[i].bt,
               procs[i].priority, procs[i].wt, procs[i].tat);
        tot_wt += procs[i].wt;
        tot_tat += procs[i].tat;
    }

    printf("Average Waiting Time = %.2f\n", tot_wt / n);
    printf("Average Turn Around Time = %.2f\n", tot_tat / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gIndex; i++) {
        printf(" P%d |", gantt[i].pid);
    }
    printf("\n");

    printf("%d", gantt[0].start);
    for (int i = 0; i < gIndex; i++) {
        printf("   %d", gantt[i].end);
    }
    printf("\n");
}
