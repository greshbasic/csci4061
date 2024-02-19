#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "util.h"

int main(){
	/*write code here*/
	bool cont = true;
	char cwd[1000];
	char input[500];

	getcwd(cwd, sizeof(cwd));
	while (cont) {
		char prompt[500] = "[4061-shell]";
		strcat(prompt, cwd);
		printf("%s $ ", prompt);
		scanf("%s", input);
		if (strcmp("exit", input) == 0) {
			cont = false;
		}
	}
	return 0;
}