//main.c program to translate the virtual addresses from the virtual.txt
//into the physical frame address. Project 3 - CSci 4061

#include <stdio.h>
#include <stdlib.h>
#include "vmemory.h"

#define INPUT_FILE "../bin/virtual.txt"

int main(int argc, char* argv[])
{
	// Declare variables as necessary

	if (argc > 2) {
		printf("Too many arguments, enter up to one argument\n");
		exit(-1);
	}

	// "?" is a conditional operator that returns the second value if the first value is true
	int policy = (argc == 2) ? 1:0;
	initialize_vmanager(policy);

	// TODO: Open the file 

	// TODO: Translate all of the virtual addresses in INPUT_FILE

	// Output the TLB at the beginning and end along with the hit rate
	
	// Output the TLB here
	// Only print the corresponding physical addresses line by line
	// Make sure to populate the TLB as you go!

	// [Hint 1]: Use the bitwise operators and masking to extract the page number and offset
	// [Hint 2]: strtol() might be useful to convert the string to an integer
	
	// Close the file

	printf("Hit rate of the cache is %f\n", get_hit_ratio());
	
	// Print the TLB here

	//Free the page table
	free_resources(); // you don't need to worry about this function
	return 0;
}
