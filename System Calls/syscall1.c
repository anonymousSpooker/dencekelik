#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t p;
    p = fork();
    if(p==0){
        // Child process
        printf("I am a Child\n");
    } else if (p>0) {
        // Parent Process
        printf("I am a Parent\n");
    }
    return 0;
}