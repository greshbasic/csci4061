
/*test machine: CSELAB_machine_name
* date: mm/dd/yy
* name: Gresham Basic, [full_name2]
* x500: basic009, [id_for_second_name]
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

	// printf(" >> Made it all the way to the end\n");

	// Not sure about this, I wonder if child process relies on parent process existing until the very very end
	// because I am getting "Conditional jump or move depends on uninitialised value(s)" errors when the following code is uncommented.
	
	// // Deallocating memory
	// for(int i = 0; i < depGraph->V; i++){

	// 	// Deallocating for each individual node in given AdjList
	// 	struct AdjListNode* currentNode = depGraph->array[i].head;
	// 	while (currentNode->next) {
	// 		struct AdjListNode* toBeFreedNode = currentNode;
	// 		currentNode = currentNode->next;
	// 		free(toBeFreedNode);
    // 	}

	// }
	
	// // Deallocating the now "empty" AdjList
	// free(depGraph->array);

	// // Deallocaating the now "empty" DepGraph
	// free(depGraph);



	return 0;
}