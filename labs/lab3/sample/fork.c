#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Child pid: %d - terminating\n", getpid());
        exit(0); /* terminate child */
    }
    else {
        pid_t cpid = wait(NULL); /* reaping parent */
        if (cpid < 0) {
            perror("Wait failed");
            return 1; 
        }
    }
    printf("Parent pid: %d - terminating\n", pid); 
    return 0;
}
