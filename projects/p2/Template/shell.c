/*test machine: csel-kh1262-18
* date: 02/28/24
* name: Gresham Basic, Elaine Nguyen
* x500: basic009, nguy4546
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "util.h"

#include <fcntl.h>
#define WRITE (O_WRONLY | O_CREAT | O_TRUNC)
#define APPEND (O_WRONLY | O_CREAT | O_APPEND)

void handle_pipe(char *tokens_before_pipe[], char *tokens_after_pipe[], int j);
void handle_pipe_and_redirect(char *tokens[], int num_tokens, int fd, bool *had_pipe);

int main() {

	// prepping prompt and cwd
	char cwd[1000];
	char input[500]; 
	char prompt[500] = "[4061-shell]";	
	char initial_cwd[500];
	getcwd(cwd, sizeof(cwd));
	getcwd(initial_cwd, sizeof(initial_cwd));
	strcat(prompt, cwd);

	while (true) {

		printf("%s $ ", prompt);
		fflush(stdout);

		ssize_t bytes_in_input = read(STDIN_FILENO, input, sizeof(input));
		if (bytes_in_input < 0) {
			perror("read");
			exit(1);
		}

		input[bytes_in_input - 1] = '\0';
		char *trimmed_input = trimwhitespace(input);

		char *tokens[100];
		int num_tokens = parse_line(trimmed_input, tokens, " ");
		int command_number;

		// the command is not a command we made
		if (get_command_type(tokens[0]) == ERROR) {
			int fd;
			int pipefd[2];
			pid_t pid = fork();
			bool had_pipe = false;

			if (pid < 0) {
				perror("fork");
			} else if (pid == 0) {
				handle_pipe_and_redirect(tokens, num_tokens, fd, &had_pipe);
				if (!had_pipe) {
					execvp(tokens[0], tokens);
				}
			} else {	
				wait(NULL);
			}
		}
		
		command_number = get_command_type(tokens[0]);

		// ls
		if (command_number == 0) {
			int fd;
			pid_t pid = fork();
			bool had_pipe = false;
			if (pid < 0) {
				perror("fork");
				exit(1);
			} else if (pid == 0) {
				handle_pipe_and_redirect(tokens, num_tokens, fd, &had_pipe); 
				if (!had_pipe) {
					char new_command[504];
					snprintf(new_command, sizeof(new_command), "%s/ls", initial_cwd);
					execvp(new_command, tokens);
				}
			} else {
				wait(NULL);
			}
		}

		// cd (made in-house instead of using execv and ./cd)
		if (command_number == 1) {
			if (chdir(tokens[1])) {
				perror("cd");
				exit(1);
			}
			
			strcpy(prompt, "[4061-shell]");
			getcwd(cwd, sizeof(cwd));
			printf("Entering directory: %s\n", cwd);
			strcat(prompt, cwd);

		}

		// wc
		if (command_number == 2) {
			pid_t pid = fork();
			int fd;
			bool had_pipe = false;
			if (pid < 0) {
				perror("fork");
				exit(1);
			} else if (pid == 0) {
				handle_pipe_and_redirect(tokens, num_tokens, fd, &had_pipe);
				if (!had_pipe) {
					char new_command[504];
					snprintf(new_command, sizeof(new_command), "%s/wc", initial_cwd);
					execvp(new_command, tokens);
				}
			} else {
				wait(NULL);
			}
		}

		// exit
		if (command_number == 3) {
			exit(0);	
		}	
	}
	
	return 0;
}

void handle_pipe_and_redirect(char *tokens[], int num_tokens, int fd, bool *had_pipe) {
	int curr_fd;
	
	// check for redirection
	for (int i = 0; i < num_tokens; i++) {
		if (strcmp(tokens[i], ">") == 0) {	// found >, so we redirect to a file in append mode, replace the > with NULL to prep for execvp
			fd = open(tokens[i + 1], WRITE);
			if(fd == -1){
				perror("open");
				exit(-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			tokens[i] = NULL;
		} else if (strcmp(tokens[i], ">>") == 0) { // found >>, so we redirect to a file in write mode, replace the >> with NULL to prep for execvp
			fd = open(tokens[i + 1], APPEND);
			if(fd == -1){
				perror("open");
				exit(-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			tokens[i] = NULL;
		} 
	}
	// check for pipe
	for (int i = 0; i < num_tokens; i++) {	
		if (tokens[i] != NULL) {
	
			if (strcmp(tokens[i], "|") == 0){	// found a pipe, so we handle the pipe and set the had_pipe flag to true
				// pipe stuff
				*had_pipe = true;

				char *tokens_after_pipe[100];
				int iter = 0;
				for (int j = i + 1; j < num_tokens; j++) {
					tokens_after_pipe[iter] = tokens[j];
					iter += 1;
				}

				int num_tokens_before_pipe = i;
				char *tokens_before_pipe[100];
				int j = 0;
				for (j; j < num_tokens_before_pipe; j++) {
					tokens_before_pipe[j] = tokens[j]; 
				}

				handle_pipe(tokens_before_pipe, tokens_after_pipe, j); // call the function to handle the pipe
				
			}
		}
	}
}

void handle_pipe(char *tokens_before_pipe[], char *tokens_after_pipe[], int j) {
	int original_stdout_fd = dup(STDOUT_FILENO);
	int original_stdin_fd = dup(STDIN_FILENO);
	int pipefd[2];
	int fork_status;
	int pipe_success = pipe(pipefd);

	if (pipe_success < 0) {
		perror("pipe");
		exit(1);
	}

	int pid = fork();
	if (pid < 0) {
		perror("pipe fork");
		exit(1);
	} else if (pid == 0) {	 // child fork, takes on the first command
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
			perror("dup2");
			exit(1);
		}
		close(pipefd[1]);
		execvp(tokens_before_pipe[0], tokens_before_pipe); 
		exit(1);
	} else { // parent fork, takes on the second command
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(original_stdout_fd, STDOUT_FILENO);
		execvp(tokens_after_pipe[0], tokens_after_pipe);
		exit(1); 
	} 

	dup2(original_stdin_fd, STDIN_FILENO); // restore stdin
	close(pipefd[0]);
	close(pipefd[1]);
	
	return;
}
