#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    printf("Printing the current working directory:\n");
    execlp("pwd", "pwd", NULL);
    
    // If execlp returns, it means there was an error
    perror("execlp failed");
    return 1;
    
}
