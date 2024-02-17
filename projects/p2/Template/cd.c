#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>

void cd(char* arg){
	/*insert code here*/
	if (chdir(arg)) {
		perror("cd");
		return;
	}

	char current_dir[100];
	if (getcwd(current_dir, sizeof(current_dir))) {
		printf("%s\n", current_dir);
	} else {
		perror("pwd");
		return;
	}
	
	return;
}

int main(int argc, char** argv){

	if(argc<2){
		printf("Pass the path as an argument\n");
		return 0;
	}
	cd(argv[1]);
	return 0; 
}