#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include "linked_list.h"

// initialize head
node *head = NULL;

// sequence counter
int seq_ctr = 0;


char line[1000];
//Read the file on a line by line basis

// not really sure what this is meant to do, just read? do something based on line number? like why does it have line_no as an argument?
// i assume the idea is to read a specific line, but the comment of "read the file on a line by line basis" is misleading
char* read_line(char* fname, int line_no)  {
	int current_line = 0;
	FILE *fp = fopen(fname, "r");
	char* result = fgets(line, sizeof(line), fp);
	while (result != NULL) {
		if (current_line == line_no) {
			fclose(fp);
			return line;
		}
		current_line += 1;
		result = fgets(line, sizeof(line), fp);
	}
} 

//traverse the linked list
void traversal(node *head) {
	while (head != NULL) {
		printf("%d, %d, %s\n", head->seq_no, head->line_no, head->content);
		head = head->next;
	}
}

// insert the node into the linked list
void insert(node **phead, node *newnode) {
	while (*phead != NULL) {
		node* next_node = (*phead)->next;
		phead = &next_node;
	}
	*phead = newnode;
}

//create a new node structure
node* create_node(int line_no, char *line) {
	node *newnode = (node*) malloc(sizeof(node));

	newnode->seq_no = seq_ctr + 1;
	seq_ctr += 1;

	newnode->line_no = line_no;

	newnode->content = (char*) malloc(strlen(line) + 1);
	strcpy(newnode->content, line);

	newnode->next = NULL;

	return newnode;
}
