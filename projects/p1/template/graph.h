#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// A structure to represent an adjacency list node 
struct AdjListNode { 
    int dest;
    struct AdjListNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList{
    int visit;
    struct AdjListNode *head; 
}; 
  
// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices  
// in graph) 
struct DepGraph{ 
    int V; 
    struct AdjList* array; 
}; 

// TODO: Declare functions in the graph.c
// A utility function to create a new adjacency list node 

  
// A utility function that creates a graph from the input text file

  
// Adds an edge to an directed graph 


// Recursive DFS call


// execute the generated graph


#endif