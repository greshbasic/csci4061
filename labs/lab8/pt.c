#include <stdio.h>
#include <stdlib.h>

#define LVL_ONE 1024
#define LVL_TWO 64
#define LVL_THREE 64
#define PHYS_SIZE (LVL_ONE + LVL_TWO + LVL_THREE)
#define VALID 4

// set up the lab 9 page table
// note: has many unallocated entries representing unused virtual addresses
int ***setup_page_table() {
	int ***pt = malloc(sizeof(int **) * LVL_ONE);
	
	// arbitrary
	int valid_indices[VALID] = {1, 5, 9, 10};
	
	for (int i = 0; i < LVL_ONE; i++) {
		int flag = 0;
		for (int j = 0; j < VALID; j++) {
			if (i == valid_indices[j]) {
				flag = 1;
			}
		}
		if (flag) {
			pt[i] = malloc(sizeof(int **) * LVL_TWO);
			for (int j = 0; j < LVL_TWO; j++) {
				pt[i][j] = malloc(sizeof(int *) * LVL_THREE);
				for (int k = 0; k < LVL_THREE; k++) {
					pt[i][j][k] = (k * 13) + (k % 31);
				}
			}
		} else {
			pt[i] = NULL;
		}
	}

	return pt;
}

// should only be used to free the page table set up by the above function
void free_page_table(int ***pt) {
	for (int i = 0; i < LVL_ONE; i++) {
		for (int j = 0; j < LVL_TWO; j++) {
			if (pt[i] != NULL && pt[i][j] != NULL) {
				free(pt[i][j]);
			}
		}
		if (pt[i] != NULL) {
			free(pt[i]);
		}
	}
	free(pt);
}

