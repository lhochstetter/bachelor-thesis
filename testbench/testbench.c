#include <stdio.h>
#include <stdlib.h>

#include "test.h"

unsigned int err_cnt = 0;

void to_bit_string(char *c, unsigned char n) {
	for (int i = 0; i < 8; i++) {
		c[7 - i] = (n % 2) ? '1' : '0';
		n /= 2;
	}
}

void print_results() {
	printf("\n################################################################################\n");
	if (err_cnt)
		printf("%d errors occured!\n", err_cnt);
	else
		printf("Test passed!\n");
	printf("################################################################################\n\n");
}


int main(void) {

	int ret_val = 0;

	test();
	print_results();
	
	if (err_cnt)
		ret_val = 1;
	
	return ret_val;
}
