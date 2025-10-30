//fcfs
#include <stdio.h>

struct process {
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    // Sort processes by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int cur_time = p[0].at;
    for (int i = 0; i < n; i++) {
        if (cur_time < p[i].at)
            cur_time = p[i].at;  // CPU idle until next process arrives

        cur_time += p[i].bt;
        p[i].ct = cur_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Average Turnaround and Waiting Times
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
    avg_tat /= n;
    avg_wt /= n;
    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    // Gantt Chart
    printf("\nGantt Chart:\n ");

    int time = p[0].at;
    for (int i = 0; i < n; i++) {
        // Handle idle CPU time
        if (time < p[i].at) {
            for (int j = 0; j < (p[i].at - time); j++)
                printf("--");
            printf(" ");
            printf("\n| IDLE |");
            time = p[i].at;
        }

        // Draw line for process burst time
        for (int j = 0; j < p[i].bt; j++)
            printf("--");
        printf(" ");
        time += p[i].bt;
    }

    printf("\n|");

    // Print process IDs in the chart
    time = p[0].at;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            printf(" IDLE |");
            time = p[i].at;
        }
        for (int j = 0; j < p[i].bt - 1; j++)
            printf(" ");
        printf("P%d", i + 1);
        for (int j = 0; j < p[i].bt - 1; j++)
            printf(" ");
        printf("|");
        time += p[i].bt;
    }

    printf("\n ");
    time = p[0].at;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            for (int j = 0; j < (p[i].at - time); j++)
                printf("--");
            printf(" ");
            time = p[i].at;
        }
        for (int j = 0; j < p[i].bt; j++)
            printf("--");
        printf(" ");
        time += p[i].bt;
    }

    printf("\n%d", p[0].at);
    for (int i = 0; i < n; i++) {
        if (p[i].at > p[i-1].ct)
            printf("  %d", p[i].at);
        printf("  %d", p[i].ct);
    }

    printf("\n");
    return 0;
}

//sjf
#include <stdio.h>
#include <limits.h>

typedef struct {
    int id;
    int at, bt;
    int ct, tat, wt;
    int is_completed;
} Process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (n <= 0) return 0;

    Process p[n];
    int execution_order[n];
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].is_completed = 0;
    }

    // Find the earliest arrival
    int min_arrival = p[0].at;
    for (int i = 1; i < n; i++)
        if (p[i].at < min_arrival)
            min_arrival = p[i].at;

    int completed = 0;
    int current_time = min_arrival;

    while (completed < n) {
        int shortest_idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].is_completed && p[i].at <= current_time) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    shortest_idx = i;
                } else if (p[i].bt == min_bt && p[i].at < p[shortest_idx].at) {
                    shortest_idx = i;
                }
            }
        }

        if (shortest_idx == -1) {
            current_time++;
        } else {
            p[shortest_idx].ct = current_time + p[shortest_idx].bt;
            p[shortest_idx].tat = p[shortest_idx].ct - p[shortest_idx].at;
            p[shortest_idx].wt = p[shortest_idx].tat - p[shortest_idx].bt;
            p[shortest_idx].is_completed = 1;

            total_tat += p[shortest_idx].tat;
            total_wt += p[shortest_idx].wt;

            execution_order[completed++] = shortest_idx;
            current_time = p[shortest_idx].ct;
        }
    }

    printf("\n--- SJF Scheduling Results ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    // Gantt Chart
    printf("\n--- Gantt Chart ---\n|");
    int last_time = min_arrival;
    for (int i = 0; i < n; i++) {
        int idx = execution_order[i];
        if (p[idx].at > last_time) {
            printf(" IDLE |");
        }
        printf(" P%d |", p[idx].id);
        last_time = p[idx].ct;
    }
    printf("\n%d", min_arrival);
    last_time = min_arrival;
    for (int i = 0; i < n; i++) {
        int idx = execution_order[i];
        if (p[idx].at > last_time) printf("    %d", p[idx].at);
        printf("    %d", p[idx].ct);
        last_time = p[idx].ct;
    }
    printf("\n");

    return 0;
}

//roundrobin
#include <stdio.h>

typedef struct {
    int id;           // Process ID
    int at, bt;       // Arrival Time, Burst Time
    int rem_bt;       // Remaining Burst Time
    int ct, tat, wt;  // Completion, Turnaround, Waiting Time
} Process;

int main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the Time Quantum: ");
    scanf("%d", &tq);

    if (n <= 0 || tq <= 0) return 0;

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].rem_bt = p[i].bt;
    }

    int ready_queue[100];
    int front = 0, rear = 0;
    int current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    int gantt_p[200], gantt_t[200];
    int gantt_count = 0;

    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // Add any processes arriving at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            ready_queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {  // No process ready → CPU idle
            gantt_p[gantt_count] = -1;
            current_time++;
            gantt_t[gantt_count] = current_time;
            gantt_count++;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].at <= current_time) {
                    ready_queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = ready_queue[front++];
        int run_for = (p[idx].rem_bt < tq) ? p[idx].rem_bt : tq;
        p[idx].rem_bt -= run_for;
        current_time += run_for;

        gantt_p[gantt_count] = p[idx].id;
        gantt_t[gantt_count] = current_time;
        gantt_count++;

        // Add any newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= current_time) {
                ready_queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].rem_bt > 0) {
            ready_queue[rear++] = idx;  // Requeue
        } else {
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            completed++;
        }
    }

    // Results
    printf("\n--- Round Robin Scheduling Results ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    // Gantt Chart
    printf("\n--- Gantt Chart ---\n|");
    for (int i = 0; i < gantt_count; i++) {
        if (gantt_p[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", gantt_p[i]);
    }
    printf("\n0");
    for (int i = 0; i < gantt_count; i++) {
        printf("%4d", gantt_t[i]);
    }
    printf("\n");

    return 0;
}

//priority 
#include <stdio.h>
#include <limits.h> // For INT_MAX

// Define a process structure
typedef struct {
    int id;              // Process ID
    int at, bt, priority; // Arrival, Burst, Priority
    int ct, tat, wt;     // Completion, Turnaround, Waiting times
    int is_completed;    // Completion flag
} Process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0) return 0;

    Process p[n];
    int execution_order[n]; // To store execution sequence
    float total_tat = 0, total_wt = 0;

    // 1. Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, and Priority for P%d: ", i);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].id = i;
        p[i].is_completed = 0;
    }

    int completed_count = 0;
    int current_time = 0;
    int exec_idx = 0; // For Gantt chart order

    // 2. Scheduling loop
    while (completed_count < n) {
        int selected_idx = -1;
        int highest_priority = INT_MAX;

        // Select the ready process with the highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].is_completed) {
                if (selected_idx == -1 || p[i].priority < highest_priority ||
                    (p[i].priority == highest_priority && p[i].at < p[selected_idx].at)) {
                    highest_priority = p[i].priority;
                    selected_idx = i;
                }
            }
        }

        if (selected_idx == -1) {
            // CPU idle
            current_time++;
        } else {
            // Execute the selected process
            p[selected_idx].ct = current_time + p[selected_idx].bt;
            p[selected_idx].tat = p[selected_idx].ct - p[selected_idx].at;
            p[selected_idx].wt = p[selected_idx].tat - p[selected_idx].bt;
            p[selected_idx].is_completed = 1;

            total_tat += p[selected_idx].tat;
            total_wt += p[selected_idx].wt;

            execution_order[exec_idx++] = selected_idx;
            completed_count++;
            current_time = p[selected_idx].ct;
        }
    }

    // 3. Display process table
    printf("\n--- Priority Scheduling (Non-Preemptive) Results ---\n");
    printf("PID\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    // 4. Gantt Chart
    printf("\n--- Gantt Chart ---\n");
    printf("|");

    int last_ct = 0;
    for (int i = 0; i < exec_idx; i++) {
        int idx = execution_order[i];

        // Handle idle time
        if (p[idx].at > last_ct) {
            printf(" IDLE |");
            last_ct = p[idx].at;
        }

        printf(" P%d |", p[idx].id);
        last_ct = p[idx].ct;
    }

    printf("\n0");
    last_ct = 0;

    for (int i = 0; i < exec_idx; i++) {
        int idx = execution_order[i];
        if (p[idx].at > last_ct) {
            printf("     %d", p[idx].at);
            last_ct = p[idx].at;
        }
        printf("     %d", p[idx].ct);
        last_ct = p[idx].ct;
    }
    printf("\n");

    return 0;
}


//priority-preemp
#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completed;
};

int main() {
    int n, completed = 0, current_time = 0, min_priority, shortest;
    float total_waiting = 0, total_turnaround = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time, Burst Time and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = 0;
    }

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    while (completed != n) {
        shortest = -1;
        min_priority = 9999;

        // Find process with highest priority (lowest priority number)
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].completed == 0) {
                if (p[i].priority < min_priority ||
                   (p[i].priority == min_priority && p[i].arrival_time < p[shortest].arrival_time)) {
                    min_priority = p[i].priority;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            current_time++; // No process ready
            continue;
        }

        // Run the chosen process for 1 unit of time
        p[shortest].remaining_time--;
        current_time++;

        // If process completed
        if (p[shortest].remaining_time == 0) {
            p[shortest].completed = 1;
            completed++;
            p[shortest].turnaround_time = current_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;

            total_waiting += p[shortest].waiting_time;
            total_turnaround += p[shortest].turnaround_time;

            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                   p[shortest].pid,
                   p[shortest].arrival_time,
                   p[shortest].burst_time,
                   p[shortest].priority,
                   p[shortest].waiting_time,
                   p[shortest].turnaround_time);
        }
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}
