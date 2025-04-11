#include <stdio.h>
#include <string.h>

struct process {
    char name[20];
    int at, bt, ct, tat, wt, remaining_bt, status;
} p[20];

struct done {
    char name[20];
    int ct, startTime;
} d[100]; // Gantt chart can have many entries due to preemption

int main(){
    int noOfProcess;
    printf("Enter the number of process: ");
    scanf("%d", &noOfProcess);

    for(int i=0; i<noOfProcess; i++){
        printf("\nEnter the Details of Process %d", i+1);
        printf("\nProcess Name: ");
        scanf("%s", p[i].name);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].status = 0;
        p[i].remaining_bt = p[i].bt;
    }

    int time = 0, completedProcess = 0, gantChartEntries = 0, prevIndex = -1;
    float totalTAT = 0, totalWT = 0;

    while(completedProcess < noOfProcess){
        int smallestIndex = -1;
        int minBT = 99999;

        for(int i=0; i<noOfProcess; i++){
            if(p[i].at <= time && p[i].remaining_bt > 0){
                if(p[i].remaining_bt < minBT){
                    minBT = p[i].remaining_bt;
                    smallestIndex = i;
                }
            }
        }

        if(smallestIndex == -1){
            // CPU is idle
            if(prevIndex != -2){
                strcpy(d[gantChartEntries].name, "Idle");
                d[gantChartEntries].startTime = time;
                prevIndex = -2;
            }
            time++;
            d[gantChartEntries].ct = time;
            if(gantChartEntries == 0 || strcmp(d[gantChartEntries].name, d[gantChartEntries - 1].name) != 0)
                gantChartEntries++;
            continue;
        }

        if(smallestIndex != prevIndex){
            strcpy(d[gantChartEntries].name, p[smallestIndex].name);
            d[gantChartEntries].startTime = time;
            if(gantChartEntries != 0 && strcmp(d[gantChartEntries].name, d[gantChartEntries - 1].name) == 0){
                // same as previous, don't increment
            } else {
                gantChartEntries++;
            }
        }

        p[smallestIndex].remaining_bt--;
        time++;

        d[gantChartEntries - 1].ct = time;

        if(p[smallestIndex].remaining_bt == 0){
            p[smallestIndex].ct = time;
            p[smallestIndex].tat = p[smallestIndex].ct - p[smallestIndex].at;
            p[smallestIndex].wt = p[smallestIndex].tat - p[smallestIndex].bt;
            p[smallestIndex].status = 1;
            completedProcess++;
        }

        prevIndex = smallestIndex;
    }

    printf("\nProcess Name | \tCompletion Time | \tTurnAroundTime | \tWaiting Time\n\n");
    for(int i=0; i<noOfProcess; i++){
        printf("    %s\t\t%d\t\t\t%d\t\t\t%d\n", p[i].name, p[i].ct, p[i].tat, p[i].wt);
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\n\nGANTT CHART");
    printf("\n----------------------------------------------\t\n");
    for(int i=0; i<gantChartEntries; i++){
        printf("|%s", d[i].name);
    }
    printf(" |");
    printf("\n----------------------------------------------\n");
    for(int i=0; i<gantChartEntries; i++){
        printf("%d\t", d[i].startTime);
    }
    printf("%d\t\n", d[gantChartEntries-1].ct);

    printf("\n\nAverage Turn-Around-Time: %f", (totalTAT/noOfProcess));
    printf("\nAverage Waiting-Time: %f", (totalWT/noOfProcess));

    return 0;
}
