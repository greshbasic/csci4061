#include <stdio.h>
#include <stdlib.h>

// declarations of provided page table setup/teardown functions
// you don't need to do anything with this
int ***setup_page_table();
void free_page_table(int ***);

// TODO: Complete this function to translate virtual addresses to physical addresses
int translate(int virtual_addr, int ***page_table) {
	int physical_addr;

	// virtual_addr is size of 30 bits
	// Your code goes here. Split the virtual address into 3 indexes and an offset. Then index into page_table and combine the result with the offset
	// start from most significant to least significant (left to right), order starts from 1st.

	// 10 most significant bit 
	int index_1 = virtual_addr >> 20;

	// 11th to 16th most significant bits (inclusive)
	int index_2 = virtual_addr >> 14 & 0x3F;

	// 17th to 22th most significant bits (inclusive)
	int index_3 = virtual_addr >> 8 & 0x3F;

	// 8 least significant bits
	int offset = virtual_addr & 0xFF;

	physical_addr = (page_table[index_1][index_2][index_3] << 8) + offset;

	return physical_addr;
}

int main(int argc, char *argv[]) {
	int ***page_table = setup_page_table();

	// Don't get confused by this array. 
	// As mentioned in slides: we assume only use the 30 least significant bits of virtural address for physical address conversion.
	int addrs[4] = {0x0012ff67, 0x001459ea, 0x009999ff, 0x00abcdef};

	for (int i = 0; i < 4; i++) {
		printf("Translation of %x: %x\n", addrs[i], translate(addrs[i], page_table));
	}

	free_page_table(page_table);
	return 0;
}



