#include "main.h"

// hint: to access the files or directories in the parent directory, use "../name_of_your_data"
int main(int argc, char **argv) {
	printf(" >> Made it to the very beginning\n");
	// Validate command-line argument.
	// Uncomment section below and fill out the condition of the if branch
	if (argc < 2 || argc > 3) {
		printf("Incorrect number of arguments...\n");
		printf("Usage 1: ./depGraph input_text_file\n");
		printf("Usage 2: ./depGraph -p input_text_file\n");
		exit(1);
	}

	// mode 0 DFS
	// mode 1 parallel
	int mode;
	FILE *input;

	// Uncomment the section below and complete the fopen arguments
	printf(" >> Made it to mode setting\n");
	if (argc == 2) {
		mode = 0;
		input = fopen(argv[1], "r");
	} else if (argc ==3) {
		mode = 1;
		input = fopen(argv[2], "r");
	}

	
	if(!input) {
		printf("File %s not found...\n", argv[1]);
		printf("Exiting...\n");
		exit(1);
	}

	printf(" >> Made it to graph creation\n");

	char cmds[32][550];
	struct DepGraph *depGraph = createDepGraph(input, cmds);

	fclose(input);

	processGraph(depGraph, cmds, mode);

	printf(" >> Made it all the way to the end\n");

	return 0;
}