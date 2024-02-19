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

	read = getline(&line, &len, file);			// keep getline'ing lines until there are none left
	while (read >= 0) {
		line_count += 1;
		read = getline(&line, &len, file);
	}

	fclose(file);

	return line_count;
}

int wc_w(char* path){
	// coding in c is so much fun
	//       ^  ^ ^  ^  ^    ^
	// hello world!
	//      ^
	// banana

	// word count = num_spaces + 1?
	// ^ as long as file isn't blank

	int word_count = 0;
	FILE *file;
	char curr_char;
	char prev_char;

	file = fopen(path, "r");
	if (!file) {
		perror("wc");
	}

	curr_char = fgetc(file);
	while (curr_char != EOF) {								//											     |		
		if (curr_char == ' ' || curr_char == '\n') {	    // found a space or newline						 v	
			if (prev_char != ' ' && prev_char != '\n') {    // is this a space AFTER a character? ("character ")
				word_count += 1;							// if so, then we have seen +1 words
			}
		}
		prev_char = curr_char;
		curr_char = fgetc(file);
	}

	return word_count;
}

int wc_c(char* path){
	int char_count = 0;
	FILE *file;
	char curr_char;
	char prev_char;

	file = fopen(path, "r");
	if (!file) {
		perror("wc");
	}

	curr_char = fgetc(file);		// using same idea as wc_l, just keep fgetc'ing chars until there are none left
	while (curr_char != EOF) {	
		char_count += 1;
		curr_char = fgetc(file);
	}

	return char_count;
}

void wc(int mode, char* path){
	/*Feel free to change the templates as needed*/
	/*insert code here*/
	int line_count;
	int word_count;
	int char_count;

	if (mode == 1) {
		line_count = wc_l(path);
		printf("%d %s\n", line_count, path);
	} else if (mode == 2) {
		word_count = wc_w(path);
		printf("%d %s\n", word_count, path);
	} else if (mode == 3) {
		char_count = wc_c(path);
		printf("%d %s\n", char_count, path);
	} else {
		line_count = wc_l(path);
		word_count = wc_w(path);
		char_count = wc_c(path);
		printf(" %d  %d %d %s\n", line_count, word_count, char_count, path);
	}
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