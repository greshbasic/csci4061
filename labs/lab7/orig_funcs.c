#ifndef ORIG
#define ORIG

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DIM_3d 100
#define DIM_2d 100
#define DIM_1d 1000000

// TODO: This function has bad spatial locality. Make it more efficient!
// Hint: What is the access pattern for the flattened 3D array in memory?
int f1_orig(int ***array_3d) {
	int sum = 0;
	for (int i = 0; i < DIM_3d; i++) {
		for (int j = 0; j < DIM_3d; j++) {
			for (int k = 0; k < DIM_3d; k++) {
				sum += array_3d[k][j][i];
			}
		}
	}
	return sum;
}

// TODO: This function has bad temporal locality. Make it more efficient!
// Hint: Is there a better way to track a running sum?
int f2_orig(int *array) {
	int sums[DIM_1d];
	sums[0] = array[0];
	for (int i = 1; i < DIM_1d; i++) {
		sums[i] = sums[i-1] + array[i];
	}
	return sums[DIM_1d-1];
}

// TODO: This function has bad spatial AND temporal locality. Make it more efficient!
// Hint: Is the access pattern optimal? Can you save entries to reduce the number of memory accesses?
// Bonus: Try to implement matrix multiplication with blocking for further speedups if you are ambitious
int **f3_orig(int **array1, int **array2) {
	// initialize result array
	int **result = malloc(DIM_2d * sizeof(int*));
	for (int i = 0; i < DIM_2d; i++) {
		result[i] = malloc(DIM_2d * sizeof(int));
		memset(result[i], 0, DIM_2d * sizeof(int));
	}

	// actual computation
	for (int j = 0; j < DIM_2d; j++) {
		for (int k = 0; k < DIM_2d; k++) {
			for (int i = 0; i < DIM_2d; i++) {
				result[i][j] += array1[i][k] * array2[k][j];
			}
		}
	}
	return result;
}

#endif

