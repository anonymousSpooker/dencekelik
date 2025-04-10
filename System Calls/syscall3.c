#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t p;
    p = fork();
    if (p == 0){
        printf("\n\nIn Child Process:\n");
        printf("PID of Parent Process: %d\n", getppid());
        printf("PID of Current Process: %d", getpid());
    } else if (p > 0){
        printf("\nIn Parent Process:\n");
        printf("PID of Parent Process: %d\n", getppid());
        printf("PID of Current Process: %d", getpid());
    }
    return 0;
}