#include <stdio.h>
#include <unistd.h>

int main(){
    fork();
    fork();
    fork();
    fork();
    printf("Hello World\n");
    return 0;
}

// Output: 16 Times Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World
// Hello World