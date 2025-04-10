#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t p;
    p = fork();
    if (p==0){
        printf("\nIn Child Process:\n");
        for(int i=10; i>0; i--)
            printf("%d ", i);
    } else if (p>0){
        printf("In Parent Process:\n");
        for(int i=1; i<=10; i++)
            printf("%d ", i);
    }
    return 0;
}