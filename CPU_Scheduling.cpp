#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;              
    int arrivalTime;     
    int burstTime;       
    int completionTime;  
    int waitingTime;     
    int turnaroundTime;
} Process;

void calculateTimes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

void FCFS(Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
    }

    calculateTimes(processes, n);
}

void SJF(Process processes[], int n) {
    bool completed[n];
    int currentTime = 0, completedCount = 0;

    for (int i = 0; i < n; i++) {
        completed[i] = false;
    }

    while (completedCount < n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime) {
                if (shortest == -1 || processes[i].burstTime < processes[shortest].burstTime) {
                    shortest = i;
                }
            }
        }

        if (shortest != -1) {
            currentTime += processes[shortest].burstTime;
            processes[shortest].completionTime = currentTime;
            completed[shortest] = true;
            completedCount++;
        } else {
            currentTime++;
        }
    }

    calculateTimes(processes, n);
}

void printTable(Process processes[], int n) {
    printf("\nProcess Table:\n");
    printf("+------------+--------------+-----------+----------------+----------------+---------------+\n");
    printf("| Process ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("+------------+--------------+-----------+----------------+----------------+---------------+\n");

    for (int i = 0; i < n; i++) {
        printf("|     P%-6d|      %-7d|     %-7d|        %-9d|        %-9d|      %-7d|\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
    printf("+------------+--------------+-----------+----------------+----------------+---------------+\n");
}

void generateGanttChart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("---------");
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("   P%-3d  |", processes[i].id);
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("---------");
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("        %d", processes[i].completionTime);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("\nEnter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process P%d:\n", processes[i].id);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    printf("\nChoose a scheduling algorithm:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(processes, n);
            break;
        case 2:
            SJF(processes, n);
            break;
        default:
            printf("Invalid choice!\n");
            return 1;
    }

    printTable(processes, n);
    generateGanttChart(processes, n);

    return 0;
}
