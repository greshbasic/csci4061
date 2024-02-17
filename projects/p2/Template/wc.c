#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>

int wc_l(char* path){
	int line_count = 0;
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	file = fopen(path, "r");
	if (!file) {
		perror("wc");
	}

	read = getline(&line, &len, file);
	while (read >= 0) {
		line_count += 1;
		read = getline(&line, &len, file);
	}

	fclose(file);

	return line_count;
}

int wc_w(char* path){
	int word_count = 0;




	return word_count;
}

int wc_c(char* path){
	int char_count = 0;




	return char_count;
}

void wc_all(char* path){
	int line_count = wc_l(path);
	int word_count = wc_w(path);
	int char_count = wc_c(path);

	printf("%d %d %d %s\n", line_count, word_count, char_count, path);
}

void wc(int mode, char* path){
	/*Feel free to change the templates as needed*/
	/*insert code here*/
	int count;

	if (mode == 1) {
		count = wc_l(path);
	} else if (mode == 2) {
		count = wc_w(path);
	} else if (mode == 3) {
		count = wc_c(path);
	} else {
		wc_all(path);
		return;
	}

	printf("%d %s\n", count, path);
	return;
}

int main(int argc, char** argv){
	if(argc>2){
		if(strcmp(argv[1], "-l") == 0) { 
			wc(1, argv[2]);
		} else if(strcmp(argv[1], "-w") == 0) { 
			wc(2, argv[2]);
		} else if(strcmp(argv[1], "-c") == 0) { 
			wc(3, argv[2]);
		} else {
			printf("Invalid arguments\n");
		}
	} else if (argc==2){
	 	if(strcmp(argv[1], "-l") == 0) { 
			wc(1, NULL);
		} else if(strcmp(argv[1], "-w") == 0) { 
			wc(2, NULL);
		} else if(strcmp(argv[1], "-c") == 0) { 
			wc(3, NULL);
		} else {
    		wc(0, argv[1]);
    	}
  	} else {
  		wc(0,NULL);
  	}

	return 0;
}