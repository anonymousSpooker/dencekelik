#include <stdio.h>
#include <string.h>

struct process {
    char name[20];
    int at, bt, ct, tat, wt, status; // Status checks whether the process is completed or not
} p[20], temp;

struct done {
    char name[20];
    int ct, startTime; // Start time of the process execution
} d[20];

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
        printf("Burst TIme: ");
        scanf("%d", &p[i].bt);
        p[i].status = 0;
    }

    int time, completedProcess, gantChartEntries, cpuIdle, found, smallestBTIndex;
    time = 0; completedProcess = 0; gantChartEntries = 0; cpuIdle =  0; found = 0;

    for(completedProcess; completedProcess < noOfProcess;){
        for(int i=0; i<noOfProcess; i++){
            if(time >= p[i].at && p[i].status == 0){
                if(found == 0){
                    smallestBTIndex = i;
                    found = 1;
                } else if(p[smallestBTIndex].bt > p[i].bt){
                    smallestBTIndex = i;
                }
            }
        }
        if(cpuIdle == 0 && found == 0){
            strcpy(d[gantChartEntries].name, "Idle");
            d[gantChartEntries].startTime = time;
            time++;
            cpuIdle = 1;
        } else if (found == 1){
            if(cpuIdle == 1){
                d[gantChartEntries].ct = time;
                gantChartEntries++;
                cpuIdle = 0;
            }
            strcpy(d[gantChartEntries].name, p[smallestBTIndex].name);
            d[gantChartEntries].startTime = time;
            d[gantChartEntries].ct = time + p[smallestBTIndex].bt;

            time = d[gantChartEntries].ct;

            p[smallestBTIndex].status = 1;
            p[smallestBTIndex].ct = d[gantChartEntries].ct;
            p[smallestBTIndex].tat = p[smallestBTIndex].ct - p[smallestBTIndex].at;
            p[smallestBTIndex].wt = p[smallestBTIndex].tat - p[smallestBTIndex].bt;

            gantChartEntries++;
            completedProcess++;
        } else time++;
        found = 0;
    }

    float totalTAT, totalWT;

    printf("\nProcess Name | \tCompletion Time | \tTurnAroundTime | \tWaiting Time\n\n");
    for(int i=0; i<noOfProcess; i++){
        printf("    %s\t\t%d\t\t\t%d\t\t\t%d\n", p[i].name, p[i].ct, p[i].tat, p[i].wt);
        totalTAT+=p[i].tat;
        totalWT+=p[i].wt;
    }

    printf("\n\nGANTT CHART");
    printf("\n----------------------------------------------\t\n");
    for(int i=0; i<noOfProcess; i++){
        printf("|");
        printf("%s", d[i].name);
    }
    printf(" |");
    printf("\n----------------------------------------------\n");
    for(int i=0; i<noOfProcess; i++){
        printf("%d\t",d[i].startTime);
    }
    printf("%d\t\n",d[gantChartEntries-1].ct);
    printf("\n\nAverage Turn-Around-Time: %f", (totalTAT/noOfProcess));
    printf("\nAverage Waiting-Time: %f", (totalWT/noOfProcess));
    return 0;
}