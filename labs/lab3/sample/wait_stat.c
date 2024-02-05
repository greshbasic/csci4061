#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int stat;
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed"); // Error check
        return 1;   
    }
    else if (pid == 0) {
        exit(0);                         /* terminate child */
    }
    else {
        pid_t cpid = wait(&stat);      /* reaping parent */
        if (cpid < 0) {              /* Error check */      
            perror("Wait failed");
            return 1; 
        }
    }
    if (WIFEXITED(stat)) {
        printf("Exit status: %d\n", WEXITSTATUS(stat));
    }
    else if (WIFSIGNALED(stat)) {
        printf("Killed by signal: %d\n", WTERMSIG(stat));
    }

    return 0;

}