//Implement the API modeling the translation of virtual page address to a
//physical frame address. We assume a 32 bit virtual memory and physical memory.
//Access to the page table is only via the CR3 register.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vmemory.h"

#define OUT_TLB "../bin/tlb_out.txt"

bool FIFO_policy = true;
int **cr3;
//
// You can declare global variables necessary for your TLB implementation here
// TODO 1: Add global variables here as necessary
// TODO 2: Define the TLB with correct size and dimension
// [Hint]: You can use static variables like hit_count, miss_count, front or back for FIFO
//

static void initialize_tlb()
{
	//TODO: Initialize the TLB

}
//
// More static helper functions can be implemented here
//


// The implementation of get_vpage_cr3 is provided in 
// an object file, so no need to re-implement it
void initialize_vmanager(int policy) 
{
	// Set LFU policy when passed as a parameter
	if (policy)
		FIFO_policy = false;
	// Set base pointer to page table
	cr3 = get_vpage_cr3();
	
	
	// You can add other initialization here as necessary
}

//
// The implementation of the following functions is required
//
int translate_virtual_address(unsigned int v_addr)
{
	// [Hint 1]: Use the bitwise operators to extract the page number and offset
	// [Hint 2]: Useful bitwise operators: >>, <<, &, |
	//TODO 1: return -1 if the second-level page table is NULL
	return -1;
}

void print_physical_address(int frame, int offset)
{
	//TODO : Print the physical address in the correct format
	return;
}

int get_tlb_entry(int n)
{
	//TODO 1: Get the frame from the TLB if it exists
	//TODO 2: increment the hit and miss count accordingly
	return -1;
}

void populate_tlb(int v_addr, int p_addr) 
{
	//TODO 1: Implement the FIFO policy
	//TODO 2: [Extra Credit]: Implement the LFU policy
	return;
}


// hit ratio = #hits / (#hits + #misses), # = total number of
float get_hit_ratio()
{
	//TODO
	return 0.0;
}

// Write to the file denoted by OUT_TLB
void print_tlb()
{
	//TODO 1: Open the file in append mode
	//TODO 2: Write the TLB to the file in the correct format
	

	return;
}
