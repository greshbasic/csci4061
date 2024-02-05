#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t child_pid;
    int child_status;

    // TODO 1: Fork a child process to run the command "cat sample.txt" using "execlp()"
    if (child_pid == -1) {
        
    } else if (child_pid == 0) {
        
        }

    else {

        // TODO 2: The parent should wait and print out the child's exit code using "wait()"

        }
        printf("Child exited with status %d\n", child_status);

    return 0;
}
