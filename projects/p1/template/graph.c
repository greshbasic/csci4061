#include "graph.h"

struct AdjListNode* newAdjListNode(int dest){ 
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
}  

// TODO: This function is to read files. And based on the file content, build a DepGraph (please refer to figure 1 in project1.pdf).
// Please take a close look at the file structure on page 2, section 4, "Sample Input."
struct DepGraph* createDepGraph(FILE *input, char cmds[][550]){
	ssize_t read;
	size_t len = 0;
	char *line = NULL;
    int V;
    int numOfNodes = 0;
    struct AdjList* array;
    char *token;
    int source;
    int dest;
    int i = 0;


    // First, let's read the number of nodes and all commands from the input file!
    // 1. Get the number of nodes using getline() and sscanf()
    read = getline(&line, &len, input);
    sscanf(line, "%d", &numOfNodes);

    // 2. Skip the blank line.
    read = getline(&line, &len, input);

    // 3. Read all commands from the file using a loop until reach the source-destination section (reaches a newline character '\n')
    // We won't do anything to cmds[][550] in this function OTHER THAN reading all commands from it.
    read = getline(&line, &len, input);
    while (read != -1 && strcmp(line, "\n") != 0) {
        strcpy(cmds[i], line);
        i++;
        read = getline(&line, &len, input);
    }

    // Now, let's move to Graph Creation!
    // Dynamically allocate the memory space to the DepGraph.
    struct DepGraph* graph = (struct DepGraph*) malloc(sizeof(struct DepGraph));

    // Then, initialize the value of V (Number of nodes), and Dynamically allocate the memory space to DepGraph's AdjList array
    V = numOfNodes;
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));


    // Initialize each element in the DepGraph's AdjList array
    for(int i = 0; i < V; i++){
        graph->array[i].head = NULL;
    }

    // Now, let's build edges to this DepGraph
    // Inside each loop iteration, use getline(), strtok(), and sscanf() to tokenize sources and destinations from the file.
    // Sources and destinations represent edges between commands. (please refer to figure 1 in project1.pdf)
    // Add edge to the DepGraph using addEdge(), source, and destination
 
    read = getline(&line, &len, input);
    while (read > 0) {                                    // read is OK
        char *currentToken = strtok(line, " \n");
        if (currentToken) {                                 // if there is something here
            int destination;
            int source;
            sscanf(currentToken, "%d", &source);            // assign it to source
            currentToken = strtok(NULL, " \n");
            if (currentToken) {                             // if there is something else here
                sscanf(currentToken, "%d", &destination);   // assign it to destination
                addEdge(graph, source, destination);
            }
        }
        read = getline(&line, &len, input);
    }
   
    return graph; 
}

// TODO: This function adds an edge to the node inside DepGraph's AdjList array. 
// Recall how to insert elements to the linked list in lab 1.
void addEdge(struct DepGraph* graph, int src, int dest){
    // If the head of the AdjList array element at the index of src is null, 
    // we create a new node using newAdjListNode()
    // and make the head of the AdjList array element at the index of src points to it.
    // printf("Adding new node to NULL head...\n");
    if (graph->array[src].head == NULL){
        graph->array[src].head = newAdjListNode(dest);
        return;
    }

    // If the head of the AdjList array element at the index of src is NOT null,
    // then we will traverse to the next AdjListNode until we find a node is pointing to a null.
    // Create a new node using newAdjListNode() and make the current node point to it.
    // printf("Adding new node to head\n");
    struct AdjListNode* currentNode = graph->array[src].head;
    while (currentNode->next) {
        currentNode = currentNode->next;
    }

    currentNode->next = newAdjListNode(dest);
    return;
}

// TODO: This function writes the DephGraph to the output file and executes the commands.
// Please take a close look at the file structure on page 3, section 5, "Sample Output".
void DFSVisit(struct DepGraph* graph, int node, char cmds[][550], int mode) {

    // visited already
    if (graph->array[node].visit) {
        return;
    }

    // now visited
    graph->array[node].visit = 1;

    if (!mode) {
        struct AdjListNode* currentNode = graph->array[node].head;
        while (currentNode) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                exit(1);
            } else if (pid == 0) {
                DFSVisit(graph, currentNode->dest, cmds, mode);
                exit(0);
            } else {
                waitpid(pid, NULL, 0);
                currentNode = currentNode->next;
            }
        }
    }

    // Let's move on to complete the code that will be executed in each recursion.
    // Open the results.txt file. If the file does not exist, then create one using c code.
    FILE *results;
    results = fopen("results.txt", "a");

    // Get the PID of the current process and its parent process
    pid_t pid = getpid();
    pid_t ppid = getppid();
        
    // Write the PIDS and commands to the results.txt
    fprintf(results, "%d %d %s", pid, ppid, cmds[node]);
    fclose(results);

    // execute the command at the given node.
    system(cmds[node]);
    // char cmds_clone[550];
    // int tracker = 0;
    // char *tokens[100];
    // strcpy(cmds_clone, cmds[node]);

    // char *current_token = strtok(cmds_clone, " ");
    // while(current_token){
    //     tokens[tracker] = current_token;
    //     current_token = strtok(NULL, " ");
    //     tracker += 1;
    // }

    // execvp(tokens[0], tokens);
}

void processGraph(struct DepGraph* graph, char cmds[][550], int mode){
    int i;
    int child = fork();
    if (child == 0) {
	   DFSVisit(graph, 0, cmds, mode);
    }
    else {
        wait(NULL);
    }
}
