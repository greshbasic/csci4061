#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "util.h"

int main() {
	/*write code here*/
	char cwd[1000];	// random number
	char input[500]; // random number
	char prompt[500] = "[4061-shell]";	// random number
	getcwd(cwd, sizeof(cwd));
	strcat(prompt, cwd);

	while (true) {

		printf("%s $ ", prompt);
		fgets(input, sizeof(input), stdin);
		char *trimmed_input = trimwhitespace(input);
		char *tokens[100];
		int num_tokens = parse_line(trimmed_input, tokens, " ");
		int command_number;
		char command[5];

		if (get_command_type(tokens[0]) == ERROR) {
			// exec(tokens[0]) something like this, if it errors then quit
			pid_t pid = fork();
			if (pid < 0) {
				perror("fork");
			} else if (pid == 0) {
				execlp(tokens[0], tokens[0], tokens[1], NULL);
				exit(1);	// only occurs if there was an error with exec
			} else {	
				wait(NULL);
			}
		}
		
		command_number = get_command_type(tokens[0]);
		if (command_number == 0) {
			pid_t pid = fork();
			if (pid < 0) {
				perror("fork");
			} else if (pid == 0) {
				if (tokens[1] == NULL) {
					execlp("./ls", "ls", NULL);
				}

				if (strcmp(tokens[1], "-R") == 0) {
					execlp("./ls", "ls", "-R", tokens[2], NULL);
				} else if (tokens[1] != NULL) {
					execlp("./ls", "ls", tokens[1], NULL);
				} 

			} else {
				wait(NULL);
			}
		}

		// it doesnt actually stay in the directory after executing the command
		if (command_number == 1) {
			pid_t pid = fork();
			if (pid < 0) {
				perror("fork");
			} else if (pid == 0) {
				execlp("./cd", "cd", tokens[1], NULL);
			} else {
				wait(NULL);
			}
		}

		if (command_number == 2) {
			pid_t pid = fork();
			if (pid < 0) {
				perror("fork");
			} else if (pid == 0) {
				if (strcmp(tokens[1], "-l") == 0) {
					execlp("./wc", "wc", "-l", tokens[2], NULL);					
				} else if (strcmp(tokens[1], "-w") == 0) {
					execlp("./wc", "wc", "-w", tokens[2], NULL);				
				} else if (strcmp(tokens[1], "-c") == 0) {
					execlp("./wc", "wc", "-c", tokens[2], NULL);	
				} else {
					execlp("./wc", "wc", tokens[1], NULL);					
				}
			} else {
				wait(NULL);
			}
		}

		if (command_number == 3) {
			printf("Exiting shell\n");
			exit(0);
		}	
	}
	
	return 0;
}