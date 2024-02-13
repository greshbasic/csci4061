
/*test machine: csel-kh1262-18
* date: 02/13/24
* name: Gresham Basic, Elaine Nguyen
* x500: basic009, nguy4546
*/


#include "main.h"

// hint: to access the files or directories in the parent directory, use "../name_of_your_data"
int main(int argc, char **argv) {
	// printf(" >> Made it to the very beginning\n");
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
	// printf(" >> Made it to mode setting\n");
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

	// printf(" >> Made it to graph creation\n");

	char cmds[32][550];
	struct DepGraph *depGraph = createDepGraph(input, cmds);

	fclose(input);

	processGraph(depGraph, cmds, mode);
	
	// Deallocating memory
	for(int i = 0; i < depGraph->V; i++){

		// Deallocating for each individual node in given AdjList
		struct AdjListNode* currentNode = depGraph->array[i].head;
		while (currentNode->next) {
			struct AdjListNode* toBeFreedNode = currentNode;
			currentNode = currentNode->next;
			free(toBeFreedNode);
    	}

	}
	
	// Deallocating the now "empty" AdjList
	free(depGraph->array);

	// Deallocaating the now "empty" DepGraph
	free(depGraph);

	return 0;
}